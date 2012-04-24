/**
 *  プラグインのインターフェースの定義.
 * @file plugin.h.
 * @author yatagai.
 */

#ifndef METATOOLSPLUGIN_H
#define METATOOLSPLUGIN_H

#include "MetaToolsPlugin_global.h"
#include <QtGui>
#include <string>

namespace meta_tools
{

class METATOOLSPLUGINSHARED_EXPORT IPlugin
{
public:
    IPlugin();
    ~IPlugin();

    bool Start();
    bool Closing();
    bool Close();

    bool SendMessage(const std::string &target_puligin_name, const std::string &message_type, void *param) const;
    void LogWrite(const std::string &message) const;
    void LogWriteLine(const std::string &message) const;
    void DebugLogWrite(const std::string &message) const;
    void DebugLogWriteLine(const std::string &message) const;

    void AddMenuWidget(QWidget *add_widget, const std::string &add_tab_name);
    void AddToolWidget(QWidget *add_widget);

    bool IsExecute() const
    {
        return m_is_execute;
    }

public:
    virtual const char* GetName() const = 0;
    virtual const char* GetExt() const = 0;
    virtual const char* GetAuthor() const = 0;
    virtual const char* GetVersion() const = 0;
    virtual bool IsStartUp() const
    {
        return false;
    }

protected:
    virtual bool ReceiveMessage(const IPlugin * /*sender*/, const std::string &/*message_type*/, void * /*param*/)
    {
        return true;
    }
    virtual bool OnStart() = 0;
    virtual bool OnClosing()
    {
        return true;
    }
    virtual bool OnClose()
    {
        return true;
    }

private:
    bool m_is_execute;
};

}  // end namespace meta_tools
#endif // METATOOLSPLUGIN_H
