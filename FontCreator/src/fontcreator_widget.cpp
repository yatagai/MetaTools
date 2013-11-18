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
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, false);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, false);
    QImage font(
        temp,
        draw_bitmap->width,
        draw_bitmap->height,
        QImage::Format_ARGB32
    );
    QPointF position(0.0f, 0.0f);
    painter.drawImage(position, font);
    delete temp;
}

}

/**
 *  @brief		コンストラクタ.
 */
FontCreatorWidget::FontCreatorWidget() :
    QWidget()
  , m_ui(new Ui::MainForm())
  , m_graphics_scene(nullptr)
  , m_font_loader(new font_creator::FontLoader())
  , m_texture_count(0)
  , m_texture_width(256)
  , m_texture_height(256)
  , m_font_color(0xFF, 0xFF, 0xFF)
  , m_outline_color(0x00, 0x00, 0xFF)
  , m_bg_color(0x88, 0x88, 0x88)
{
    m_ui->setupUi(this);
    setAcceptDrops(true);

    m_graphics_scene = new QGraphicsScene(0);
    m_ui->graphicsView->setScene(m_graphics_scene);

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
            this, SLOT(OnChangeOutlineEnable(bool)));

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

    if (m_graphics_scene)
    {
        ClearImage();

        delete m_graphics_scene;
        m_graphics_scene = nullptr;
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
                QFileInfo(url.toLocalFile()).suffix().toLower() == "ttf")
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
                QFileInfo(url.toLocalFile()).suffix().toLower() == "ttf")
            {
                QString file_name = QFileInfo(url.toLocalFile()).filePath();
                m_ui->font_path->setText(QFileInfo(url.toLocalFile()).fileName());
                if (m_font_loader->Load(file_name.toStdString().c_str()))
                {
                    m_ui->create_text->setPlainText("");
                    CreateFontCache();
                    UpdateImage(m_texture_width, m_texture_height);
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

/**
 *  @breif      update image.
 *  @param  in  tex_width テクスチャ幅.
 *  @param  in  tex_height テクスチャ高さ.
 */
void FontCreatorWidget::UpdateImage(int tex_width, int tex_height)
{
    ClearImage();

    if (!m_font_loader->HasFace())
    {
        return;
    }

    QImage invalidate_image(tex_width, tex_height, QImage::Format_RGB888);
    invalidate_image.fill(m_bg_color);
    QImage new_image;
    QPoint offset(CHARACTOR_MARGIN, CHARACTOR_MARGIN);
    QImage *current_texture = nullptr;

    float outline_width = m_ui->outline_enable->isChecked() ? m_ui->outline_width->value() : 0.0f;
    float font_height = m_font_loader->GetMaxFontHeight() + outline_width * 2.0f;

    for (unsigned int chara_index = 0; chara_index < m_font_loader->GetFontInfoCount(); ++chara_index)
    {       
        const font_creator::FontLoader::FontInfo &info = m_font_loader->GetFontInfo(chara_index);
        float font_width = info.width + outline_width * 2.0f;
        bool next_line = (offset.x() + font_width + CHARACTOR_MARGIN) >
                tex_width;
        if (next_line)
        {
            offset.setX(CHARACTOR_MARGIN);
            offset.setY(offset.y() + font_height + CHARACTOR_MARGIN);
            if (offset.y() + font_height + CHARACTOR_MARGIN > tex_height)
            {
                if (current_texture)
                {
                    QGraphicsPixmapItem *new_item = m_graphics_scene->addPixmap(QPixmap::fromImage(*current_texture));
                    new_item->setOffset(0.0f, m_texture_count * (TEXTURE_MARGIN + m_texture_height));
                    ++m_texture_count;
                    current_texture = nullptr;
                }
            }
        }
        if (current_texture == nullptr)
        {
            new_image = invalidate_image.copy();
            offset = QPoint(CHARACTOR_MARGIN, CHARACTOR_MARGIN);
            current_texture = &new_image;
        }

        // 文字描画.
        QPainter painter(current_texture);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
        painter.setRenderHint(QPainter::HighQualityAntialiasing, true);

        QTransform matrix;
        matrix.translate(offset.x() + outline_width - info.bearing_x,
                         offset.y() + m_font_loader->GetMaxAscend() + outline_width);
        matrix.rotate(0.0f);
        matrix.scale(1.0f, 1.0f);
        painter.setTransform(matrix);

        // ペンとブラシ.
        QPen transparent_pen(QColor(0, 0, 0, 0));
        QPen out_line_pen(m_outline_color);
        out_line_pen.setWidthF(outline_width * 2.0f);
        QBrush transparent_brush(QColor(0, 0, 0, 0));
        QBrush outline_brush(m_outline_color);
        QBrush fill_brush(m_font_color);

        // 輪郭線描画.
        if (info.has_outline)
        {
            if (m_ui->outline_enable->isChecked())
            {
                painter.setPen(out_line_pen);
                painter.setBrush(outline_brush);
                painter.drawPath(info.path);
            }
            // 塗描画.
            painter.setPen(transparent_pen);
            painter.setBrush(fill_brush);
            painter.drawPath(info.path);
        }
        else
        {
            DrawFontToQImage(current_texture, &info.fill,
                             offset.x(), offset.y(), m_font_color);
        }

        // 境界表示.
        if (m_ui->bound->isChecked())
        {
            painter.setRenderHint(QPainter::Antialiasing, false);
            painter.setRenderHint(QPainter::HighQualityAntialiasing, false);
            matrix = QTransform();
            matrix.translate(0.0f, 0.0f);
            matrix.rotate(0.0f);
            matrix.scale(1.0f, 1.0f);
            painter.setTransform(matrix);

            if (m_bg_color.red() * 0.3f + m_bg_color.green() * 0.59f + m_bg_color.blue() * 0.11f >=
                0xFF)
            {
                painter.setPen(QPen(QBrush(Qt::black), 1.0f));
            }
            else
            {
                painter.setPen(QPen(QBrush(Qt::white), 1.0f));
            }
            painter.setBrush(transparent_brush);
            painter.drawRect(offset.x(), offset.y(), font_width, font_height);
        }
        painter.end();
        offset.setX(offset.x() + font_width + CHARACTOR_MARGIN);
    }
    if (current_texture)
    {
        QGraphicsPixmapItem *new_item = m_graphics_scene->addPixmap(QPixmap::fromImage(*current_texture));
        new_item->setOffset(0.0f, m_texture_count * (TEXTURE_MARGIN + tex_height));
        ++m_texture_count;

        current_texture->save("test.bmp", "BMP");
    }
    UpdateScale();
}

/**
 *  @breif      clear image.
 */
void FontCreatorWidget::ClearImage()
{
    m_graphics_scene->clear();
    m_texture_count = 0;
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
    UpdateImage(m_texture_width, m_texture_height);
}

/**
 *  @breif      フォントサイズ変更イベント.
 *  @param  in  font_size フォントサイズ.
 */
void FontCreatorWidget::OnFontSizeChanged(int /*font_size*/)
{
    CreateFontCache();
    UpdateImage(m_texture_width, m_texture_height);
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
    CreateFontCache();
    UpdateImage(m_texture_width, m_texture_height);
}

/**
 *  @breif      アウトライン太さ変更.
 *  @param  in  outline_width アウトライン太さ.
 */
void FontCreatorWidget::OnChangeOutlineWidth(double /*outline_width*/)
{
    CreateFontCache();
    UpdateImage(m_texture_width, m_texture_height);
}

/**
 *  @breif      テキスト変更.
 */
void FontCreatorWidget::OnTextChanged()
{
    CreateFontCache();
    UpdateImage(m_texture_width, m_texture_height);
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
    for (char16_t i = 0x3040; i < 0x30ff; ++i)
    {
        if (m_font_loader->CanRenderCharactor(i))
        {
            add.append(i);
        }
    }
    for (char16_t i = 0xff10; i < 0xff5a; ++i)
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
}

/**
 *  @breif      スケール更新.
 */
void FontCreatorWidget::UpdateScale()
{
    float scale = m_ui->scale_slider->value() / 100.0f;
    for (int i = 0; i < m_graphics_scene->items().size(); ++i)
    {
        m_graphics_scene->items().at(i)->setTransform(QTransform::fromScale(scale, scale));
    }

    m_graphics_scene->setSceneRect(0.0f, 0.0f,
                                  m_texture_width * scale, m_texture_count * (TEXTURE_MARGIN + m_texture_height) * scale);
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

        UpdateImage(m_texture_width, m_texture_height);
    }
}

/**
 *  @breif      輪郭線カラー変更.
 */
void FontCreatorWidget::OnClickOutlineColor()
{
    QColor temp = m_font_color;
    temp = QColorDialog::getColor(temp,
                                  this,
                                  "select Outline Color",
                                  QColorDialog::DontUseNativeDialog);
    if (temp.isValid())
    {
        m_outline_color = temp;
        QString style = "QWidget {background-color: " + m_outline_color.name() + ";}";
        m_ui->outline_color->setStyleSheet(style);

        UpdateImage(m_texture_width, m_texture_height);
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

        UpdateImage(m_texture_width, m_texture_height);
    }
}
