/**
 * ログプラグイン.
 * @file log_plugin.h.
 * @author yatagai.
 */
#ifndef LOG_PLUGIN_H
#define LOG_PLUGIN_H


#include<plugin.h>

namespace meta_tools
{
/**
 *  プラグイン管理クラス.
 *  @author yatagai.
 */
class LogPlugin : public IPlugin
{
public:
    LogPlugin();
    ~LogPlugin();

public:
    virtual const char* GetName() const
    {
        return "LogPlugin";
    }
    virtual const char* GetExt() const
    {
        return "Log出力プラグイン.";
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

private:
    bool OnReceiveLogPrint(const IPlugin *sender, void *param);

protected:
    virtual bool OnStart();
    virtual bool OnClose();
};

}       // end namespace meta_tools

#endif  // LOG_PLUGIN_H
