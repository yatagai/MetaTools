/**
 * プラグインウィジェット.
 * @file plugin_widget.h.
 * @author yatagai.
 */
#ifndef PLUGIN_WIDGET_H
#define PLUGIN_WIDGET_H

#include <QWidget>

namespace meta_tools
{
class IPlugin;
}

namespace Ui
{
class Plugin;
}
class PluginManagerWidget;

/**
 *  プラグインマネージャウィジェットクラス.
 *  @author yatagai.
 */
class PluginWidget : public QWidget
{
     Q_OBJECT
public:
    explicit PluginWidget(meta_tools::IPlugin* plugin, PluginManagerWidget *plugin_manager_widget);
    ~PluginWidget();

protected:
    virtual void mouseReleaseEvent(QMouseEvent *mouse_event);
    virtual void mouseMoveEvent(QMouseEvent *mouse_event);
    virtual void leaveEvent(QEvent *event);

private:
    void SetUpWidget();

private:
    void UnSelect();

private:
    Ui::Plugin *m_ui;
    meta_tools::IPlugin *m_plugin;
    PluginManagerWidget *m_plugin_manager_widget;
};

#endif // PLUGIN_WIDGET_H
