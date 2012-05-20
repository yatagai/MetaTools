/**
 *  プラグインのインターフェースの定義.
 * @file plugin.h.
 * @author yatagai.
 */

#ifndef METATOOLSPLUGIN_H
#define METATOOLSPLUGIN_H

#include "MetaToolsPlugin_global.h"
#include <string>
#include <map>
#include <functional>

class QWidget;

namespace meta_tools
{

class METATOOLSPLUGINSHARED_EXPORT IPlugin
{
public:
    IPlugin();
    ~IPlugin();

public:
    bool Start();
    bool Closing();
    bool Close();

    // message関係.
public:
    bool SendMessage(const std::string &target_puligin_name, const std::string &message_type, void *param) const;
protected:
    template<class F>
    void AddMessageFunc(const std::string &message_type, bool (F::*func)(const IPlugin*, void*))
    {
        F* cast_this = static_cast<F*>(this);
        m_message_functions.insert(std::make_pair(message_type, std::bind(func, cast_this, std::placeholders::_1, std::placeholders::_2)));
    }
private:
    bool ReceiveMessage(const IPlugin *sender, const std::string &message_type, void *param);
private:
    typedef std::map<const std::string, std::function<bool (const IPlugin * sender, void *param)> > MessageFunctionMap;
    MessageFunctionMap m_message_functions;


public:
    void LogWrite(const std::string &message) const;
    void LogWriteLine(const std::string &message) const;
    void DebugLogWrite(const std::string &message) const;
    void DebugLogWriteLine(const std::string &message) const;

public:
    void AddMenuWidget(QWidget *add_widget, const std::string &add_tab_name);
    void AddToolWidget(QWidget *add_widget);

public:
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

private:
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
