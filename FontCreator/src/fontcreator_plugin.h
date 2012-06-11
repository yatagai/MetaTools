#ifndef FONTCREATOR_H
#define FONTCREATOR_H

#include "FontCreator_global.h"
#include "../../MetaTools/src/plugin/plugin.h"

class FONTCREATORSHARED_EXPORT FontCreatorPlugin : public meta_tools::IPlugin
{
public:
    explicit FontCreatorPlugin(const meta_tools::IPlugin::AppFunctions &app_functions);
    ~FontCreatorPlugin(){};
public:
    virtual const char* GetName() const
    {
        return "FontCreator";
    }
    virtual const char* GetExp() const
    {
        return "フォント作成プラグイン";
    }
    virtual const char* GetAuthor() const
    {
        return "yatagai";
    }
    virtual const char* GetVersion() const
    {
        return "0.1a";
    }

public:
    virtual void OnClickCloseButton(QWidget * /*clicked_widget*/)
    {

    }

protected:
    virtual bool OnStart()
    {
        LogWrite("OnStart FontCreator.");
        return true;
    }

    virtual bool OnClose()
    {
        return false;
    }
};

extern "C" FONTCREATORSHARED_EXPORT meta_tools::IPlugin* CreatePlugin(const meta_tools::IPlugin::AppFunctions &app_functions)
{
    return new FontCreatorPlugin(app_functions);
}

#endif // FONTCREATOR_H
