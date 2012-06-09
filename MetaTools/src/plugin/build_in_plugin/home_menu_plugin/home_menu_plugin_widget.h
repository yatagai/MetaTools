/**
 * ホームメニュープラグインウィジェット.
 * @file home_menu_plugin_widget.h.
 * @author yatagai.
 */
#ifndef HOME_MENU_PLUGIN_WIDGET_H
#define HOME_MENU_PLUGIN_WIDGET_H
#include <QWidget>

namespace Ui
{
class HomeMenu;
}
namespace meta_tools
{
class IPlugin;
class HomeMenuPlugin;
}
class PluginManagerWidget;

/**
 *  ホームメニューウィジェットクラス.
 *  @author yatagai.
 */
class HomeMenuPluginWidget : public QWidget
{
     Q_OBJECT
public:
    explicit HomeMenuPluginWidget(meta_tools::HomeMenuPlugin* plugin);
    ~HomeMenuPluginWidget();

public:
    void OnLoadedPlugin(meta_tools::IPlugin *plugin);

private:
    void InitMenuButton();
public slots:
    void OnClickAppCloseButton();
private slots:
    void OnClickShowPluginManagerButton();
    void OnClickShowLogButton();

private:
    meta_tools::HomeMenuPlugin *m_plugin;
    Ui::HomeMenu *m_ui;

    PluginManagerWidget *m_plugin_manager_widget;
};


#endif // HOME_MENU_PLUGIN_WIDGET_H
