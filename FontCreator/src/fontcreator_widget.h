#ifndef FONTCREATOR_WIDGET_H
#define FONTCREATOR_WIDGET_H

#include "FontCreator_global.h"
#include <QWidget>
#include <QtGui>
namespace Ui {
class MainForm;
}
class QImage;
class QGraphicsScene;

namespace font_creator
{
class FontLoader;
}

class FontCreatorWidget : public QWidget
{
     Q_OBJECT
public:
    explicit FontCreatorWidget();
    ~FontCreatorWidget();
private:
    Ui::MainForm *m_ui;

public:
    void OnStart();
    void OnClose();

private:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private:
    void CreateFontCache();
    void UpdateImage(int tex_width, int tex_height);
    void ClearImage();
private:
    QGraphicsScene *m_graphics_scene;

private:
    font_creator::FontLoader *m_font_loader;
    int m_texture_count;

    // テクスチャサイズ変更.
private slots:
    void OnTextureSizeChenged(int index);
private:
    int m_texture_size;

    // フォントサイズ変更.
private slots:
    void OnFontSizeChanged(int font_size);

    // 輪郭線変更.
private slots:
    void OnChangeOutlineEnable(bool checked);
    void OnChangeOutlineWidth(double outline_width);

    // テキスト変更.
private slots:
    void OnTextChanged();

    // ASCIIかな漢字ボタンクリック.
private slots:
    void OnClickASCII();
    void OnClickKana();
    void OnClickKanji();

    // スケール変更.
private slots:
    void OnScaleChenged(int value);
private:
    void UpdateScale();

    // カラー変更.
protected:
    virtual bool eventFilter(QObject *object, QEvent *event);
private:
    void OnClickFontColor();
    void OnClickBGColor();
private:
    QColor m_font_color;
    QColor m_bg_color;
};

#endif // FONTCREATOR_WIDGET_H
