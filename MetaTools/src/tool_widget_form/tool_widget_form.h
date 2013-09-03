#ifndef META_TOOLS_TOOL_WIDGET_FORM_H
#define META_TOOLS_TOOL_WIDGET_FORM_H

#include <QDockWidget>

namespace Ui
{
class ToolWidgetForm;
}
namespace meta_tools
{
class IPlugin;
class ToolWidgetForm : public QDockWidget
{
    Q_OBJECT
public:
    explicit ToolWidgetForm(const IPlugin *plugin, QWidget *main_view);
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

public:
    void OnClickCloseButton();

};
}       // end namespace meta_tools.
#endif // META_TOOLS_TOOL_WIDGET_FORM_H.
