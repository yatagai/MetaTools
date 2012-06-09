#ifndef META_TOOLS_TOOL_WIDGET_FORM_H
#define META_TOOLS_TOOL_WIDGET_FORM_H

#include <QWidget>

namespace Ui
{
class ToolWidgetForm;
}
namespace meta_tools
{
class IPlugin;
class ToolWidgetForm : public QWidget
{
    Q_OBJECT
public:
    explicit ToolWidgetForm(const IPlugin *plugin);
    ~ToolWidgetForm();
    
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
private:
    Ui::ToolWidgetForm *m_ui;
    QWidget* m_child;

protected:
    void resizeEvent(QResizeEvent *event);

public:
    void OnClickCloseButton();

};
}       // end namespace meta_tools.
#endif // META_TOOLS_TOOL_WIDGET_FORM_H.
