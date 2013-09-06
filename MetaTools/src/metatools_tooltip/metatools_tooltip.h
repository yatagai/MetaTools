/**
 * tooltipクラスの定義.
 * @file metatools_tooltip..
 * @author yatagai.
 */

#ifndef METATOOLS_TOOLTIP_H
#define METATOOLS_TOOLTIP_H

#include <QWidget>

namespace Ui {
class MetaToolsToolTip;
}

namespace meta_tools
{
class IPlugin;
/**
 *  ツールチップクラス.
 *  @author yatagai.
 */
class MetaToolsToolTip : public QWidget
{
    Q_OBJECT
    
public:
    explicit MetaToolsToolTip(QWidget *paren, const IPlugin *plugin);
    ~MetaToolsToolTip();

public:
    const IPlugin* GetPlugin() const
    {
        return m_plugin;
    }
private:
    const IPlugin *m_plugin;

public:
    QWidget* GetChildWidget() const
    {
        return m_child;
    }
    void SetChildWidget(QWidget *child);
    void SetLabel(const char* label);
private:
    Ui::MetaToolsToolTip *m_ui;
    QWidget* m_child;

private slots:
    void OnClickCloseButton();

protected:
    void paintEvent(QPaintEvent *event);
};

}       // end namespace meta_tools.
#endif // METATOOLS_TOOLTIP_H.
