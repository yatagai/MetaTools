#include "fontcreator_widget.h"
#include "ui_main_form.h"
#include "fontloader.h"
#include <QGraphicsPixmapItem>
#include <QTransform>
#include <QColorDialog>

namespace
{
const int CHARACTOR_MARGIN(3);
const int TEXTURE_MARGIN(25);
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
  , m_texture_size(256)
  , m_font_color(0xFF, 0xFF, 0xFF)
  , m_bg_color(0x00, 0x00, 0x00)
{
    m_ui->setupUi(this);
    setAcceptDrops(true);

    m_graphics_scene = new QGraphicsScene(0);
    m_ui->graphicsView->setScene(m_graphics_scene);

    // texture size combo box.
    m_ui->texture_size_list->addItem("256x256", QVariant(256));
    m_ui->texture_size_list->addItem("512x512", QVariant(512));
    m_ui->texture_size_list->addItem("1024x1024", QVariant(1024));
    m_ui->texture_size_list->addItem("2048x2048", QVariant(2048));
    m_ui->texture_size_list->addItem("4096x4096", QVariant(4096));
    connect(m_ui->texture_size_list, SIGNAL(currentIndexChanged(int)),
            this, SLOT(OnTextureSizeChenged(int)));
    m_ui->texture_size_list->setCurrentIndex(1);
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
    // QTransform scale_matrix = QTransform::fromScale(2, 2);
    // m_ui->graphicsView->setTransform(scale_matrix);
    // スケールスライダー
    connect(m_ui->scale_slider, SIGNAL(valueChanged(int)),
            this, SLOT(OnScaleChenged(int)));


    // default color.
    QString style = "QWidget {background-color: " + m_font_color.name() + ";}";
    m_ui->font_color->setStyleSheet(style);
    style = "QWidget {background-color: " + m_bg_color.name() + ";}";
    m_ui->bg_color->setStyleSheet(style);
    m_ui->font_color->installEventFilter(this);
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

    ClearImage();
    if (m_graphics_scene)
    {
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
            if (QFileInfo(url.toLocalFile()).suffix() == "ttc" ||
                QFileInfo(url.toLocalFile()).suffix() == "ttf")
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
            if (QFileInfo(url.toLocalFile()).suffix() == "ttc" ||
                QFileInfo(url.toLocalFile()).suffix() == "ttf")
            {
                QString file_name = QFileInfo(url.toLocalFile()).filePath();
                m_ui->font_path->setText(QFileInfo(url.toLocalFile()).fileName());
                if (m_font_loader->Load(file_name.toStdString().c_str()))
                {
                    m_ui->create_text->setPlainText("");
                    CreateFontCache();
                    UpdateImage(m_texture_size, m_texture_size);
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
    for (unsigned int chara_index = 0; chara_index < m_font_loader->GetFontInfoCount(); ++chara_index)
    {
        const font_creator::FontLoader::FontInfo &info = m_font_loader->GetFontInfo(chara_index);
        if (offset.x() + (int)info.width + CHARACTOR_MARGIN >= m_texture_size)
        {
            offset.setX(CHARACTOR_MARGIN);
            float font_height_max = m_ui->font_size->value();
            if (m_ui->outline_enable)
            {
                font_height_max += static_cast<float>(m_ui->outline_width->value() * 2.0);
            }
            offset.setY(offset.y() + font_height_max + CHARACTOR_MARGIN);
            if (offset.y() + m_ui->font_size->value() + CHARACTOR_MARGIN >= m_texture_size)
            {
                if (current_texture)
                {
                    QGraphicsPixmapItem *new_item = m_graphics_scene->addPixmap(QPixmap::fromImage(*current_texture));
                    new_item->setOffset(0.0f, m_texture_count * (TEXTURE_MARGIN + m_texture_size));
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
        for (int i = (int)info.offst_y; i < ((int)info.height + (int)info.offst_y); ++i)
        {
            for (int j = 0; j < (int)info.width; ++j)
            {
                unsigned char color = reinterpret_cast<unsigned char*>(info.bitmap)[(i - (int)info.offst_y) * (int)info.width + j];
                float colorf = color / 255.0f;
                unsigned char red = m_font_color.redF() * 255 * colorf + m_bg_color.redF() * 255 * (1.0f - colorf);
                unsigned char green = m_font_color.greenF() * 255 * colorf + m_bg_color.greenF() * 255 * (1.0f - colorf);
                unsigned char blue = m_font_color.blueF() * 255 * colorf + m_bg_color.blueF() * 255 * (1.0f - colorf);
                current_texture->bits()[((i + offset.y()) * m_texture_size + (j + offset.x())) * 3 + 0] = red;
                current_texture->bits()[((i + offset.y()) * m_texture_size + (j + offset.x())) * 3 + 1] = green;
                current_texture->bits()[((i + offset.y()) * m_texture_size + (j + offset.x())) * 3 + 2] = blue;
            }
        }
        offset.setX(offset.x() + (int)info.width + CHARACTOR_MARGIN);
    }
    if (current_texture)
    {
        QGraphicsPixmapItem *new_item = m_graphics_scene->addPixmap(QPixmap::fromImage(*current_texture));
        new_item->setOffset(0.0f, m_texture_count * (TEXTURE_MARGIN + m_texture_size));
        ++m_texture_count;
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
    m_texture_size = m_ui->texture_size_list->itemData(index).toInt();
    UpdateImage(m_texture_size, m_texture_size);
}

/**
 *  @breif      フォントサイズ変更イベント.
 *  @param  in  font_size フォントサイズ.
 */
void FontCreatorWidget::OnFontSizeChanged(int /*font_size*/)
{
    OnTextChanged();
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
    OnTextChanged();
}

/**
 *  @breif      アウトライン太さ変更.
 *  @param  in  outline_width アウトライン太さ.
 */
void FontCreatorWidget::OnChangeOutlineWidth(double /*outline_width*/)
{
    OnTextChanged();
}

/**
 *  @breif      テキスト変更.
 */
void FontCreatorWidget::OnTextChanged()
{
    CreateFontCache();
    UpdateImage(m_texture_size, m_texture_size);
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
                                  m_texture_size * scale, m_texture_count * (TEXTURE_MARGIN + m_texture_size) * scale);
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

        UpdateImage(m_texture_size, m_texture_size);
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

        UpdateImage(m_texture_size, m_texture_size);
    }
}
