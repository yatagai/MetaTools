/**
 * プラグイン接続関数軍定義.
 * @file plugin_connect_func.cpp.
 * @author yatagai.
 */

#include "../save_load/save_load.h"
#include "plugin_manager/plugin_manager.h"
#include "plugin.h"
#include <QtGui>

namespace meta_tools
{

/**
 *  @brief		メッセージ送信.
 *  @author     yatagaik.
 *  @param  in  sender 送信したプラグイン.
 *  @param  in  target_plugin_name 送信先プラグイン名.
 *  @param  in  message_type メッセージ識別子.
 *  @param  in  param メッセージパラメータ.
 *  @return     true メッセージを処理した false メッセージを処理しなかった.
 */
bool AppSendMessage(const IPlugin *sender, const std::string &target_plugin_name, const std::string &message_type, void *param)
{
    return PluginManager::Order()->SendMessage(sender, target_plugin_name, message_type, param);
}

/**
 *  @brief		ログ書き込み.
 *  @author     yatagaik.
 *  @param  in  message 出力文字.
 */
void AppLogWriteRow(const std::string &message)
{
    PluginManager::Order()->LogWrite(message);
}

/**
 *  @brief		ログ書き込み.
 *  @author     yatagaik.
 *  @param  in  writer 書き込みを行ったプラグイン.
 *  @param  in  message 出力文字.
 */
void AppLogWrite(const IPlugin *writer, const std::string &message)
{
    AppLogWriteRow(std::string("[") + writer->GetName() + std::string("] ") + message);
}

/**
 *  @brief		デバッグ時ログ書き込み.
 *  @author     yatagaik.
 *  @param  in  writer 書き込みを行ったプラグイン.
 *  @param  in  message 出力文字.
 */
void AppDebugLogWrite(const IPlugin *writer, const std::string &message)
{
    AppLogWriteRow(std::string("[") + writer->GetName() + std::string("/DebugLog] ") + message);
}

/**
 *  @brief		メニューウィジェット追加.
 *  @author     yatagaik.
 *  @param  in  entry_plugin 登録したプラグイン.
 *  @param  in  add_widget 追加するウジェット.
 *  @param  in  add_tab_name 追加先タブ名.
 */
void AppAddMenuWidget(const IPlugin *entry_plugin, QWidget *add_widget, const std::string &label, const std::string &add_tab_name)
{
    PluginManager::Order()->AddMenuWidget(entry_plugin, add_widget, label, add_tab_name);
}

/**
 *  @brief		ツールウィジェット追加.
 *  @author     yatagaik.
 *  @param  in  entry_plugin 登録したプラグイン.
 *  @param  in  add_widget 追加するウジェット.
 */
void AppAddToolWidget(const IPlugin *entry_plugin, QWidget *add_widget, const std::string &label)
{
    PluginManager::Order()->AddToolWidget(entry_plugin, add_widget, label);
}

/**
 *  @brief		ウィジェットの削除.
 *  @author     yatagaik.
 *  @param  in  entry_plugin 登録したプラグイン.
 *  @param  in  add_widget 追加するウジェット.
 */
void AppRemoveWidget(const IPlugin *entry_plugin, QWidget *remove_widget)
{
    PluginManager::Order()->RemoveWidget(entry_plugin, remove_widget);
}

/**
 *  @brief		セーブデータの取得.
 *  @author     yatagaik.
 *  @param  in  entry_plugin 登録したプラグイン.
 *  @param  in  param_name パラメータ名.
 *  @return 保存値 idUndefinedで無効.
 */
const QJsonValue AppGetSaveData(const IPlugin *entry_plugin, const std::string param_name)
{
    return SaveLoad::Order()->GetSaveData(entry_plugin, param_name);
}

/**
 *  @brief		セーブデータのセット.
 *  @author     yatagaik.
 *  @param  in  entry_plugin 登録したプラグイン.
 *  @param  in  param_name パラメータ名.
 * 　@param  in  set_value セットする値.
 */
void AppSetSaveData(const IPlugin *entry_plugin, const std::string param_name, const QJsonValue &set_value)
{
    SaveLoad::Order()->SetSaveData(entry_plugin, param_name, set_value);
}

}   // end namespace meta_tools
