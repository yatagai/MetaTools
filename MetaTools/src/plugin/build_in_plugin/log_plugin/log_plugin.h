/**
 * ログプラグイン.
 * @file log_plugin.h.
 * @author yatagai.
 */
#ifndef LOG_PLUGIN_H
#define LOG_PLUGIN_H

#include "../../plugin.h"

class QWidget;
namespace Ui {
class LogWindow;
}

namespace meta_tools
{
/**
 *  プラグイン管理クラス.
 *  @author yatagai.
 */
class LogPlugin : public IPlugin
{
public:
    LogPlugin(const AppFunctions &app_functions);
    ~LogPlugin();

private:
    QWidget *m_log_window;
    Ui::LogWindow *m_log_window_ui;
    std::string m_text;
    bool m_ishide;
public:
    virtual const char* GetName() const
    {
        return "Log";
    }
    virtual const char* GetExp() const
    {
        return "Log出力プラグイン";
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

private:
    bool OnReceiveLogPrint(const IPlugin *sender, void *param);
    bool OnReceiveLogShow(const IPlugin *sender, void *param);

public:
    virtual void OnClickCloseButton(QWidget *clicked_widget);
protected:
    virtual bool OnStart();
    virtual bool OnClose();
};

}       // end namespace meta_tools

#endif  // LOG_PLUGIN_H
