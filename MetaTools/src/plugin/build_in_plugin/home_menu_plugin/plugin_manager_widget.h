/**
 * プラグインマネージャウィジェット.
 * @file plugin_manager_widget.h.
 * @author yatagai.
 */
#ifndef PLUGIN_MANAGER_WIDGET_H
#define PLUGIN_MANAGER_WIDGET_H
#include <QWidget>

namespace meta_tools
{
class IPlugin;
}
namespace Ui
{
class PluginManager;
}

/**
 *  プラグインマネージャウィジェットクラス.
 *  @author yatagai.
 */
class PluginManagerWidget : public QWidget
{
     Q_OBJECT
public:
    explicit PluginManagerWidget();
    ~PluginManagerWidget();

public:
    void AddPluginWidget(meta_tools::IPlugin *plugin);
    void Show();
    void ChangePluginExplanationText(const std::string &explanation);

protected:
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void resizeEvent(QResizeEvent *event);

private:
    Ui::PluginManager *m_ui;
};

#endif // PLUGIN_MANAGER_WIDGET_H
