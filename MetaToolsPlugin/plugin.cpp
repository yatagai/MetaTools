/**
 * プラグインのインターフェースの実装.
 * @file plugin.cpp.
 * @author yatagai.
 */

#include "plugin.h"
#include <QtGui>

namespace meta_tools
{
extern bool AppSendMessage(const IPlugin *sender, const std::string &target_plugin_name, const std::string &message_type, void *param);
extern void AppLogWrite(const IPlugin *writer, const std::string &message);
extern void AppDebugLogWrite(const IPlugin *writer, const std::string &message);
extern void AppAddMenuWidget(const IPlugin *entry_plugin, QWidget *add_widget, const std::string &add_tab_name);
extern void AppAddToolWidget(const IPlugin *entry_plugin, QWidget *add_widget);

/**
 * コンストラクタ.
 */
IPlugin::IPlugin()
    : m_is_execute(false)
{
}

/**
 * デストラクタ.
 */
IPlugin::~IPlugin()
{
}

/**
 *  プラグインの開始.
 *  @return trueで成功 falseで失敗.
 */
bool IPlugin::Start()
{
    if (OnStart())
    {
        m_is_execute = true;
    }
    return m_is_execute;
}

/**
 *  プラグインの終了してもよいか.
 *  @return trueで終了してもよい falseで終了したらダメ.
 */
bool IPlugin::Closing()
{
    return OnClosing();
}

/**
 *  プラグインの終了.
 *  @return trueで成功 falseで失敗.
 */
bool IPlugin::Close()
{
    if (OnClose())
    {
        m_is_execute = false;
    }

    return !m_is_execute;
}

/**
 *  プラグインにメッセージ送信.
 *  @param in target_plugin_name 送信先のプラグイン名.
 *  @param in message_type メッセージタイプ.
 *  @param in param パラメータ.
 */
bool IPlugin::SendMessage(const std::string &target_plugin_name, const std::string &message_type, void *param) const
{
    return AppSendMessage(this, target_plugin_name, message_type, param);
}

/**
 *  ログプラグイン.
 *  @param sender 送り主プラグイン.
 *  @param message_type メッセージタイプ.
 *  @param param パラメータ.
 *  @return trueで処理した falseで処理していない.
 */
bool IPlugin::ReceiveMessage(const IPlugin *sender, const std::string &message_type, void *param)
{
    auto it = m_message_functions.find(message_type);
    if (it != m_message_functions.end())
    {
        return it->second(sender, param);
    }
    return false;
}

/**
 *  ログに出力.
 *  @param in message 出力するメッセージ.
 */
void IPlugin::LogWrite(const std::string &message) const
{
    AppLogWrite(this, message);
}

/**
 *  ログに1行出力.
 *  @param message 出力するメッセージ.
 */
void IPlugin::LogWriteLine(const std::string &message) const
{
    AppLogWrite(this, message + "\n");
}

/**
 *  デバッグ用ログに出力.
 *  @param in message 出力するメッセージ.
 */
void IPlugin::DebugLogWrite(const std::string &message) const
{
    AppDebugLogWrite(this, message);
}

/**
 *  デバッグ用ログに1行出力.
 *  @param in message 出力するメッセージ.
 */
void IPlugin::DebugLogWriteLine(const std::string &message) const
{
    AppDebugLogWrite(this, message + "\n");
}

/**
 *  メニュー用Widget追加.
 *  @param in add_widget 追加するWidget.
 *  @param in add_tab_name 追加するタブ.
 */
void IPlugin::AddMenuWidget(QWidget *add_widget, const std::string &add_tab_name)
{
    AppAddMenuWidget(this, add_widget, add_tab_name);
}

/**
 *  ツール用Widget追加.
 *  @param in add_widget 追加するWidget.
 */
void IPlugin::AddToolWidget(QWidget *add_widget)
{
    AppAddToolWidget(this, add_widget);
}

}   // end namesapce meta_tools
