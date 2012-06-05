/**
 * プラグイン接続関数軍定義.
 * @file plugin_connect_func.cpp.
 * @author yatagai.
 */

#include "plugin_manager/plugin_manager.h"
#include "plugin.h"
#include <QtGui>

namespace meta_tools
{

/**
 *  メッセージ送信.
 *  @param in sender 送信したプラグイン.
 *  @param in target_plugin_name 送信先プラグイン名.
 *  @param in message_type メッセージ識別子.
 *  @param in param メッセージパラメータ.
 *  @return true メッセージを処理した false メッセージを処理しなかった.
 */
bool AppSendMessage(const IPlugin *sender, const std::string &target_plugin_name, const std::string &message_type, void *param)
{
    return PluginManager::Order()->SendMessage(sender, target_plugin_name, message_type, param);
}

/**
 *  ログ書き込み.
 *  @param in message 出力文字.
 */
void AppLogWriteRow(const std::string &message)
{
    PluginManager::Order()->LogWrite(message);
}

/**
 *  ログ書き込み.
 *  @param in writer 書き込みを行ったプラグイン.
 *  @param in message 出力文字.
 */
void AppLogWrite(const IPlugin *writer, const std::string &message)
{
    AppLogWriteRow(std::string("[") + writer->GetName() + std::string("] ") + message);
}

/**
 *  デバッグ時ログ書き込み.
 *  @param in writer 書き込みを行ったプラグイン.
 *  @param in message 出力文字.
 */
void AppDebugLogWrite(const IPlugin *writer, const std::string &message)
{
    AppLogWriteRow(std::string("[") + writer->GetName() + std::string("/DebugLog] ") + message);
}

/**
 *  メニューウィジェット追加.
 *  @param in entry_plugin 登録したプラグイン.
 *  @param in add_widget 追加するウジェット.
 *  @param in add_tab_name 追加先タブ名.
 */
void AppAddMenuWidget(const IPlugin *entry_plugin, QWidget *add_widget, const std::string &label, const std::string &add_tab_name)
{
    PluginManager::Order()->AddMenuWidget(entry_plugin, add_widget, label, add_tab_name);
}

/**
 *  ツールウィジェット追加.
 *  @param in entry_plugin 登録したプラグイン.
 *  @param in add_widget 追加するウジェット.
 */
void AppAddToolWidget(const IPlugin *entry_plugin, QWidget *add_widget, const std::string &label)
{
    PluginManager::Order()->AddToolWidget(entry_plugin, add_widget, label);
}

}   // end namespace meta_tools
