#include "fontcreator_widget.h"
#include "ui_main_form.h"
#include "fontloader.h"
#include <QGraphicsPixmapItem>
#include <QTransform>
#include <QColorDialog>
#include <assert.h>

namespace
{
const int CHARACTOR_MARGIN(2);
const int TEXTURE_MARGIN(25);
const int MAX_RENDER_ONE_TIME(50);
struct TextureSizeInfo
{
    const char* const text;
    int width;
    int height;
};
TextureSizeInfo TEXTURE_SIZE_LIST[] =
{
    {"256x256", 256, 256},
    {"512x256", 512, 256},
    {"512x512", 512, 512},
    {"1024x512", 1024, 512},
    {"1024x1024", 1024, 1024},
    {"2048x1024", 2048, 1024},
    {"2048x2048", 2048, 2048},
    {"4096x2048", 4096, 2048},
    {"4096x4096", 4096, 4096}
};

/**
 *  @brief	QImageへフォントの描画.
 *  @param  render_target 描画先.
 *  @param  draw_bitmap 描画するビットマップ情報.
 *  @param  draw_point_x x座標.
 *  @param  draw_point_y y座標.
 *  @param  color 色.
 */
void DrawFontToQImage(QImage *render_target,
        const font_creator::FontLoader::FontBitmap *draw_bitmap,
        float draw_point_x, float draw_point_y,
        QColor &color)
{
    unsigned char *temp = new unsigned char[draw_bitmap->width *
            draw_bitmap->height * 4];
    memset(temp, 0, draw_bitmap->width *
                   draw_bitmap->height * 4);
    for (int i = 0; i < draw_bitmap->height; ++i)
    {
        for (int j = 0; j < draw_bitmap->width; ++j)
        {
            unsigned char alpha =
                    reinterpret_cast<unsigned char*>(draw_bitmap->bitmap)[i * (int)draw_bitmap->width + j];
            temp[(i * (int)draw_bitmap->width + j) * 4] = color.blue();
            temp[(i * (int)draw_bitmap->width + j) * 4 + 1] = color.green();
            temp[(i * (int)draw_bitmap->width + j) * 4 + 2] = color.red();
            temp[(i * (int)draw_bitmap->width + j) * 4 + 3] = alpha;
        }
    }
    QTransform matrix;
    matrix.translate(draw_point_x, draw_point_y);
    matrix.rotate(0.0);
    matrix.scale(1.0, 1.0);
    QPainter painter(render_target);
    painter.setTransform(matrix);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, false);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
    QImage font(
        temp,
        draw_bitmap->width,
        draw_bitmap->height,
        QImage::Format_ARGB32
    );
    QPointF position(0.0f, 0.0f);
    painter.drawImage(position, font);
    painter.end();
    delete temp;
}

}

/**
 *  @brief		コンストラクタ.
 */
FontCreatorWidget::FontCreatorWidget() :
    QWidget()
  , m_ui(new Ui::MainForm())
  , m_view_area(new QWidget())
  , m_timer(nullptr)
  , m_font_loader(new font_creator::FontLoader())
  , m_texture_width(512)
  , m_texture_height(512)
  , m_font_color(0xaa, 0xFF, 0xFF)
  , m_outline_color(0x00, 0x00, 0xFF)
  , m_bg_color(0x50, 0x50, 0x50)
{
    m_ui->setupUi(this);
    setAcceptDrops(true);

    m_view_area->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_view_area->installEventFilter(this);
    m_view_area->setParent(m_ui->scroll_area);
    m_ui->scroll_area->setWidget(m_view_area);

    // font combo box.
    connect(m_ui->font_combo_box, SIGNAL(currentFontChanged(const QFont&)), this, SLOT(OnFontComboBoxChanged(const QFont&)));

    // texture size combo box.
    for (int i = 0; i < sizeof(TEXTURE_SIZE_LIST) / sizeof(TextureSizeInfo); ++i)
    {
        m_ui->texture_size_list->addItem(TEXTURE_SIZE_LIST[i].text, QVariant(i));
    }
    connect(m_ui->texture_size_list, SIGNAL(currentIndexChanged(int)),
            this, SLOT(OnTextureSizeChenged(int)));
    m_ui->texture_size_list->setCurrentIndex(2);
    // font size box.
    connect(m_ui->font_size, SIGNAL(valueChanged(int)),
            this, SLOT(OnFontSizeChanged(int)));
    // outline.
    connect(m_ui->outline_enable, SIGNAL(toggled(bool)),
            this, SLOT(OnChangeOutlineEnable(bool)));
    connect(m_ui->outline_width, SIGNAL(valueChanged(double)),
            this, SLOT(OnChangeOutlineWidth(double)));
    // text box.
    connect(m_ui->create_text, SIGNAL(textChanged()),
            this, SLOT(OnTextChanged()));
    // ASCIIかな漢字ボタン.
    connect(m_ui->use_all_ascii, SIGNAL(clicked()),
            this, SLOT(OnClickASCII()));
    connect(m_ui->use_all_kana, SIGNAL(clicked()),
            this, SLOT(OnClickKana()));
    connect(m_ui->use_all_kanji, SIGNAL(clicked()),
            this, SLOT(OnClickKanji()));
    // スケールスライダー.
    connect(m_ui->scale_slider, SIGNAL(valueChanged(int)),
            this, SLOT(OnScaleChenged(int)));
    // bound.
    connect(m_ui->bound, SIGNAL(toggled(bool)),
            this, SLOT(OnChangeBoundEnable(bool)));

    // default color.
    QString style = "QWidget {background-color: " + m_font_color.name() + ";}";
    m_ui->font_color->setStyleSheet(style);
    style = "QWidget {background-color: " + m_outline_color.name() + ";}";
    m_ui->outline_color->setStyleSheet(style);
    style = "QWidget {background-color: " + m_bg_color.name() + ";}";
    m_ui->bg_color->setStyleSheet(style);
    m_ui->font_color->installEventFilter(this);
    m_ui->outline_color->installEventFilter(this);
    m_ui->bg_color->installEventFilter(this);
}

/**
 *  @brief		デストラクタ.
 */
FontCreatorWidget::~FontCreatorWidget()
{
    ClearImage(false);

    if (m_view_area)
    {
        m_view_area->setParent(nullptr);
        m_ui->scroll_area->setWidget(nullptr);
        delete m_view_area;
        m_view_area = nullptr;
    }

    if (m_ui)
    {
        delete m_ui;
        m_ui = nullptr;
    }

    if (m_font_loader)
    {
        delete m_font_loader;
        m_font_loader = nullptr;
    }
}

/**
 *  @breif      スタート時処理.
 */
void FontCreatorWidget::OnStart()
{
}

/**
 *  @breif      終了時処理.
 */
void  FontCreatorWidget::OnClose()
{
}

/**
 *  @breif      描画処理.
 */
void FontCreatorWidget::paintEvent(QPaintEvent * /*event*/)
{
}

/**
 *  @breif      テクスチャ描画処理.
 */
void FontCreatorWidget::viewPaintEvent()
{
    float scale = m_ui->scale_slider->value() / 100.0f;
    QPainter painter(m_view_area);
    painter.scale(scale, scale);
    for (size_t i = 0; i < m_texture_list.size(); ++i)
    {
        painter.drawImage(TEXTURE_MARGIN,
                          TEXTURE_MARGIN + (m_texture_height + TEXTURE_MARGIN) * static_cast<int>(i),
                          *m_texture_list[i]);
        if (m_ui->bound->isChecked())
        {
            painter.drawImage(TEXTURE_MARGIN,
                              TEXTURE_MARGIN + (m_texture_height + TEXTURE_MARGIN) * static_cast<int>(i),
                              *m_bound_list[i]);
        }
    }
    painter.end();
}

/**
 *  @breif      ドラッグイベント.
 *  @param      event イベント.
 */
void FontCreatorWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        foreach (QUrl url, event->mimeData()->urls())
        {
            if (QFileInfo(url.toLocalFile()).suffix().toLower() == "ttc" ||
                QFileInfo(url.toLocalFile()).suffix().toLower() == "ttf" ||
                QFileInfo(url.toLocalFile()).suffix().toLower() == "otf" ||
                QFileInfo(url.toLocalFile()).suffix().toLower() == "fon")
            {
                event->accept();
                break;
            }
        }
    }
}

/**
 *  @breif      ドロップイベント.
 *  @param      event イベント.
 */
void FontCreatorWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        foreach (QUrl url, event->mimeData()->urls())
        {
            if (QFileInfo(url.toLocalFile()).suffix().toLower() == "ttc" ||
                QFileInfo(url.toLocalFile()).suffix().toLower() == "ttf" ||
                QFileInfo(url.toLocalFile()).suffix().toLower() == "otf" ||
                QFileInfo(url.toLocalFile()).suffix().toLower() == "fon")
            {
                QString file_name = QFileInfo(url.toLocalFile()).filePath();
                m_ui->font_path->setText(QFileInfo(url.toLocalFile()).fileName());
                if (m_font_loader->Load(file_name.toStdString().c_str()))
                {
                    m_ui->create_text->setPlainText("");
                    CreateFontCache();
                    ClearImage();
                }
                break;
            }
        }
    }
}

/**
 *  @breif      フォントキャッシュの作成.
 */
void FontCreatorWidget::CreateFontCache()
{
    if (!m_font_loader->HasFace())
    {
        return;
    }

    QString create_text = m_ui->create_text->toPlainText();
    char16_t *create_text16 = new char16_t[create_text.length() + 1];
    create_text.toWCharArray(reinterpret_cast<wchar_t*>(create_text16));
    create_text16[create_text.length()] = 0;
    font_creator::FontLoader::CreateParam create_param;
    create_param.font_size = m_ui->font_size->value();
    create_param.out_line_width = static_cast<float>(m_ui->outline_width->value());
    create_param.out_line = m_ui->outline_enable->isChecked();
    m_font_loader->CreateFontInfo(create_text16, create_param);
    delete[] create_text16;
}

void FontCreatorWidget::UpdateImageEvent()
{
    if (m_timer)
    {
        m_timer->stop();
    }
    UpdateImage(m_texture_width, m_texture_height);
}

/**
 *  @breif      update image.
 *  @param  in  tex_width テクスチャ幅.
 *  @param  in  tex_height テクスチャ高さ.
 */
void FontCreatorWidget::UpdateImage(int tex_width, int tex_height)
{
    if (!m_font_loader->HasFace())
    {
        return;
    }
    bool resize = m_texture_list.size() == 0;

    float outline_width = m_ui->outline_enable->isChecked() ? m_ui->outline_width->value() : 0.0f;
    float font_height = m_font_loader->GetMaxFontHeight() + outline_width * 2.0f;

    int render_times = 0;
    for (;
         m_render_info.render_count < m_font_loader->GetFontInfoCount() && render_times < MAX_RENDER_ONE_TIME
         ; ++m_render_info.render_count, ++render_times)
    {       
        const font_creator::FontLoader::FontInfo &info = m_font_loader->GetFontInfo(m_render_info.render_count);
        float font_width = info.width + outline_width * 2.0f;
        bool next_line = (m_render_info.offset.x() + font_width + CHARACTOR_MARGIN) >
                tex_width;
        if (next_line)
        {
            m_render_info.offset.setX(CHARACTOR_MARGIN);
            m_render_info.offset.setY(std::floorf(m_render_info.offset.y() + font_height + CHARACTOR_MARGIN));
            if (m_render_info.offset.y() + font_height + CHARACTOR_MARGIN > tex_height)
            {
                if (m_render_info.current_texture)
                {
                    m_render_info.current_texture = nullptr;
                }
            }
        }
        if (m_render_info.current_texture == nullptr)
        {
            m_render_info.offset = QPoint(CHARACTOR_MARGIN, CHARACTOR_MARGIN);
            QImage *new_image = new QImage();
            *new_image = m_render_info.invalid_image.copy();
            m_render_info.current_texture = new_image;
            m_texture_list.push_back(new_image);
            new_image = new QImage();
            *new_image = m_render_info.bound_invalid_image.copy();
            m_render_info.bound_texture = new_image;
            m_bound_list.push_back(new_image);
            resize = true;
        }

        // 文字描画.
        // ペンとブラシ.
        QPen out_line_pen(m_outline_color);
        out_line_pen.setWidthF(outline_width * 2.0f);
        out_line_pen.setCapStyle(Qt::FlatCap);
        out_line_pen.setJoinStyle(Qt::SvgMiterJoin);
        // out_line_pen.setMiterLimit(0);
        QBrush transparent_brush(QColor(0, 0, 0, 0));
        QBrush fill_brush(m_font_color);

        if (info.has_outline)
        {
            // パス描画.
            QPainter painter(m_render_info.current_texture);
            painter.setRenderHint(QPainter::Antialiasing, true);
            painter.setRenderHint(QPainter::SmoothPixmapTransform, false);
            painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
            QTransform matrix;
            matrix.translate(m_render_info.offset.x() + outline_width - info.bearing_x,
                             m_render_info.offset.y() + m_font_loader->GetMaxAscend() + outline_width);
            matrix.rotate(0.0f);
            matrix.scale(1.0f, 1.0f);
            painter.setTransform(matrix);

            if (m_ui->outline_enable->isChecked())
            {
                // painter.setPen(out_line_pen);
                painter.strokePath(info.path, out_line_pen);
            }
            // 塗描画.
            // painter.setPen(transparent_pen);
            // painter.setBrush(fill_brush);
            painter.fillPath(info.path, fill_brush);

            painter.end();
        }
        else
        {
            // ビットマップ描画.
            DrawFontToQImage(m_render_info.current_texture, &info.fill,
                             m_render_info.offset.x(),
                             m_render_info.offset.y() + info.fill.offset_y, m_font_color);
        }

        // 境界表示.
        QPainter bound_painter(m_render_info.bound_texture);
        bound_painter.setRenderHint(QPainter::Antialiasing, false);
        bound_painter.setRenderHint(QPainter::HighQualityAntialiasing, false);
        if (m_bg_color.red() * 0.3f + m_bg_color.green() * 0.59f + m_bg_color.blue() * 0.11f >=
            0x80)
        {
            bound_painter.setPen(QPen(QBrush(Qt::black), 1.0f));
        }
        else
        {
            bound_painter.setPen(QPen(QBrush(Qt::white), 1.0f));
        }
        bound_painter.setBrush(transparent_brush);
        bound_painter.drawRect(m_render_info.offset.x(), m_render_info.offset.y(), font_width, font_height);
        bound_painter.end();
        m_render_info.offset.setX(m_render_info.offset.x() + font_width + CHARACTOR_MARGIN);
    }
    if (resize)
    {
        UpdateScale();
    }

    // UpdateInfomation.
    // texture count.
    QString text = "TEXTURE COUNT ";
    QString temp;
    temp.setNum((int)m_texture_list.size());
    text += temp;
    // chara count.
    if (m_render_info.render_count < m_font_loader->GetFontInfoCount())
    {
        text += " RENDERING ";
        temp.setNum(m_render_info.render_count);
        text += temp;
        text += "/";
        temp.setNum(m_font_loader->GetFontInfoCount());
        text += temp;
    }
    else
    {
        text += " CHARACTOR COUNT ";
        temp.setNum(m_render_info.render_count);
        text += temp;
    }
    // data size.
    text += " DATA SIZE ";
    float data_size = m_texture_width * m_texture_height * static_cast<int>(m_texture_list.size());
    if (m_ui->outline_enable->isChecked())
    {
        data_size *= 2.0f;
    }
    data_size /= 1024.0f * 1024.0f;
    temp.setNum(data_size);
    text += temp;
    text += "MB";

    m_ui->infomation->setText(text);

    update();

    // タイマー再設定.
    if (m_render_info.render_count < m_font_loader->GetFontInfoCount())
    {
        if (m_timer && !m_timer->isActive())
        {
            m_timer->start(1);
        }
    }
    else if (m_timer != nullptr)
    {
        delete m_timer;
        m_timer = nullptr;
    }
}

/**
 *  @breif      clear image.
 */
void FontCreatorWidget::ClearImage(bool with_update)
{
    for (size_t i = 0; i < m_texture_list.size(); ++i)
    {
        delete m_texture_list[i];
        delete m_bound_list[i];
    }
    m_texture_list.clear();
    m_bound_list.clear();
    m_render_info.offset = QPointF(CHARACTOR_MARGIN, CHARACTOR_MARGIN);
    m_render_info.render_count = 0;
    m_render_info.current_texture = nullptr;
    m_render_info.invalid_image = QImage(m_texture_width,
                             m_texture_height,
                             QImage::Format_RGB888);
    m_render_info.bound_invalid_image = QImage(m_texture_width,
                                               m_texture_height,
                                               QImage::Format_ARGB32);
    m_render_info.invalid_image.fill(m_bg_color);
    m_render_info.bound_invalid_image.fill(Qt::transparent);

    if (with_update)
    {
        m_render_info.offset = QPoint(CHARACTOR_MARGIN, CHARACTOR_MARGIN);
        QImage *new_image = new QImage();
        *new_image = m_render_info.invalid_image.copy();
        m_render_info.current_texture = new_image;
        m_texture_list.push_back(new_image);
        new_image = new QImage();
        *new_image = m_render_info.bound_invalid_image.copy();
        m_render_info.bound_texture = new_image;
        m_bound_list.push_back(new_image);
        UpdateScale();
        update();

        if (m_timer == nullptr)
        {
            m_timer = new QTimer(this);
            connect(m_timer, SIGNAL(timeout()), this, SLOT(UpdateImageEvent()));
        }
        m_timer->start(0);
    }
}

/**
 *  @breif      フォントコンボボックス変更.
 *  @param  in  font 選択されたフォント.
 */
void FontCreatorWidget::OnFontComboBoxChanged(const QFont &font)
{
    QString font_path = QStandardPaths::standardLocations(QStandardPaths::FontsLocation)[0];
    QDir font_dir(font_path);
    if (font_dir.exists())
    {
        QStringList file_list = font_dir.entryList();
        for (int i = 0; i < file_list.size(); ++i)
        {
            QString file_name = font_path + "/" + file_list[i];
            QString family_name = font.family();
            int face_index = m_font_loader->HasFamily(file_name.toStdString().c_str(),
                family_name);
            if (face_index != -1)
            {
                m_ui->font_path->setText(QFileInfo(file_name).fileName());
                if (m_font_loader->Load(file_name.toStdString().c_str(), face_index))
                {
                    m_ui->create_text->setPlainText("");
                    CreateFontCache();
                    ClearImage();
                }
                return;
            }
        }
        m_font_loader->Unload();
        m_ui->create_text->setPlainText("");
        m_ui->font_path->setText("");
        m_ui->infomation->setText("Unsupported Font");
    }
}

/**
 *  @breif      テクスチャサイズ変更イベント.
 *  @param  in  selected_index 選択されたインデックス.
 */
void FontCreatorWidget::OnTextureSizeChenged(int index)
{
    int table_index = m_ui->texture_size_list->itemData(index).toInt();
    m_texture_width = TEXTURE_SIZE_LIST[table_index].width;
    m_texture_height = TEXTURE_SIZE_LIST[table_index].height;
    ClearImage();
}

/**
 *  @breif      フォントサイズ変更イベント.
 *  @param  in  font_size フォントサイズ.
 */
void FontCreatorWidget::OnFontSizeChanged(int /*font_size*/)
{
    CreateFontCache();
    ClearImage();
}

/**
 *  @breif      アウトライン有効/無効変更.
 *  @param  in  checked check状態.
 */
void FontCreatorWidget::OnChangeOutlineEnable(bool /*checked*/)
{
    if (m_ui->outline_enable->isChecked())
    {
        m_ui->outline_width->setEnabled(true);
    }
    else
    {
        m_ui->outline_width->setEnabled(false);
    }
    ClearImage();
}

/**
 *  @breif      アウトライン太さ変更.
 *  @param  in  outline_width アウトライン太さ.
 */
void FontCreatorWidget::OnChangeOutlineWidth(double /*outline_width*/)
{
    ClearImage();
}

/**
 *  @breif      テキスト変更.
 */
void FontCreatorWidget::OnTextChanged()
{
    CreateFontCache();
    ClearImage();
}

/**
 *  @breif      ASCIIボタンクリック.
 */
void FontCreatorWidget::OnClickASCII()
{
    QString add = "";
    for (char16_t i = 0x00; i < 0x7f; ++i)
    {
        if (m_font_loader->CanRenderCharactor(i))
        {
            add.append(i);
        }
    }
    m_ui->create_text->appendPlainText(add);
}

/**
 *  @breif      かなボタンクリック.
 */
void FontCreatorWidget::OnClickKana()
{
    QString add = "";
    // かな
    for (char16_t i = 0x3040; i < 0x30ff; ++i)
    {
        if (m_font_loader->CanRenderCharactor(i))
        {
            add.append(i);
        }
    }
    // 全角英数　半角カナ.
    for (char16_t i = 0xff10; i < 0xff9f; ++i)
    {
        if (m_font_loader->CanRenderCharactor(i))
        {
            add.append(i);
        }
    }
    m_ui->create_text->appendPlainText(add);
}

/**
 *  @breif      漢字ボタンクリック.
 */
void FontCreatorWidget::OnClickKanji()
{
    QString add = "";
    for (char16_t i = 0x4e00; i < 0x9fcc; ++i)
    {
        if (m_font_loader->CanRenderCharactor(i))
        {
            add.append(i);
        }
    }
    m_ui->create_text->appendPlainText(add);
}

/**
 *  @breif      スケール変更.
 *  @param  in  value 値.
 */
void FontCreatorWidget::OnScaleChenged(int value)
{
    QString text;
    text.setNum(value);
    text += "%";
    m_ui->scale_label->setText(text);

    UpdateScale();
    update();
}

/**
 *  @breif      境界チェック変更.
 *  @param  in  checkd チェック値.
 */
void FontCreatorWidget::OnChangeBoundEnable(bool /*checkd*/)
{
    update();
}

/**
 *  @breif      スケール更新.
 */
void FontCreatorWidget::UpdateScale()
{
    float scale = m_ui->scale_slider->value() / 100.0f;
    int width = TEXTURE_MARGIN + TEXTURE_MARGIN + m_texture_width;
    int height = TEXTURE_MARGIN + (m_texture_height + TEXTURE_MARGIN) * static_cast<int>(m_texture_list.size());

    m_view_area->setFixedSize(QSize(width * scale, height * scale));
}

/**
 *  @breif      イベントフィルタ.
 *  @param  in  object オブジェクト.
 *  @param  in  event イベント.
 *  @return trueで処理した falseで何もしなかった.
 */
bool FontCreatorWidget::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonRelease)
    {
        if (object == m_ui->font_color)
        {
            OnClickFontColor();
            return true;
        }
        else if (object == m_ui->outline_color)
        {
            OnClickOutlineColor();
            return true;
        }
        else if (object == m_ui->bg_color)
        {
            OnClickBGColor();
            return true;
        }
    }

    if(object == m_view_area && event->type() == QEvent::Paint )
    {
        viewPaintEvent();
        return true;
    }

    return false;
}

/**
 *  @breif      フォントカラー変更.
 */
void FontCreatorWidget::OnClickFontColor()
{
    QColor temp = m_font_color;
    temp = QColorDialog::getColor(temp,
                                  this,
                                  "select Font Color",
                                  QColorDialog::DontUseNativeDialog);
    if (temp.isValid())
    {
        m_font_color = temp;
        QString style = "QWidget {background-color: " + m_font_color.name() + ";}";
        m_ui->font_color->setStyleSheet(style);

        ClearImage();
    }
}

/**
 *  @breif      輪郭線カラー変更.
 */
void FontCreatorWidget::OnClickOutlineColor()
{
    QColor temp = m_outline_color;
    temp = QColorDialog::getColor(temp,
                                  this,
                                  "select Outline Color",
                                  QColorDialog::DontUseNativeDialog);
    if (temp.isValid())
    {
        m_outline_color = temp;
        QString style = "QWidget {background-color: " + m_outline_color.name() + ";}";
        m_ui->outline_color->setStyleSheet(style);

        ClearImage();
    }
}

/**
 *  @breif      BGカラー変更.
 */
void FontCreatorWidget::OnClickBGColor()
{
    QColor temp = m_bg_color;
    temp = QColorDialog::getColor(temp,
                                  this,
                                  "select BG Color",
                                  QColorDialog::DontUseNativeDialog);
    if (temp.isValid())
    {
        m_bg_color = temp;
        QString style = "QWidget {background-color: " + m_bg_color.name() + ";}";
        m_ui->bg_color->setStyleSheet(style);

        ClearImage();
    }
}
