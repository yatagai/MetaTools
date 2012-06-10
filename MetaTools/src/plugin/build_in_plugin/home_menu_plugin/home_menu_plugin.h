/**
 * ホームメニュープラグイン.
 * @file home_menu_plugin.h.
 * @author yatagai.
 */
#ifndef HOME_MENU_PLUGIN_H
#define HOME_MENU_PLUGIN_H

#include "../../plugin.h"
class QWidget;
class QIcon;
class HomeMenuPluginWidget;

namespace meta_tools
{
class IPlugin;
/**
 *  ホームメニュークラス.
 *  @author yatagai.
 */
class HomeMenuPlugin : public IPlugin
{
public:
    HomeMenuPlugin(const AppFunctions &app_functions);
    ~HomeMenuPlugin();
public:
    virtual const char* GetName() const
    {
        return "HomeMenu";
    }
    virtual const char* GetExp() const
    {
        return "MetaToolsのホームメニュープラグイン";
    }
    virtual const char* GetAuthor() const
    {
        return "yatagai";
    }
    virtual const char* GetVersion() const
    {
        return "0.8b";
    }
    virtual bool IsStartUp() const
    {
        return true;
    }

public:
    virtual void OnClickCloseButton(QWidget *clicked_widget);
protected:
    virtual bool OnStart();
    virtual bool OnClose();

private:
    bool OnLoadedPluginMessage(const IPlugin *sender, void *param);

private:
    HomeMenuPluginWidget *m_home_menu_widget;
};

}       // end namespace meta_tools

#endif  // HOME_MENU_PLUGIN_H
