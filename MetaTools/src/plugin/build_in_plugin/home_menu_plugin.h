/**
 * ホームメニュープラグイン.
 * @file home_menu_plugin.h.
 * @author yatagai.
 */
#ifndef HOME_MENU_PLUGIN_H
#define HOME_MENU_PLUGIN_H


#include<plugin.h>

namespace meta_tools
{
/**
 *  ホームメニュークラス.
 *  @author yatagai.
 */
class HomeMenuPlugin : public IPlugin
{
public:
    HomeMenuPlugin();
    ~HomeMenuPlugin();
public:
    virtual const char* GetName() const
    {
        return "HomeMenuPlugin";
    }
    virtual const char* GetExt() const
    {
        return "ホームメニュープラグイン.";
    }
    virtual const char* GetAuthor() const
    {
        return "yatagai.";
    }
    virtual const char* GetVersion() const
    {
        return "0.8b";
    }
    virtual bool IsStartUp() const
    {
        return true;
    }

protected:
    virtual bool OnStart();
    virtual bool OnClose();
};

}       // end namespace meta_tools

#endif  // HOME_MENU_PLUGIN_H
