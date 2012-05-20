/**
 * プラグイン管理クラスの実装.
 * @file plugin_manager.h.
 * @author yatagai.
 */

#include "plugin_manager.h"

namespace meta_tools
{
PluginManager* PluginManager::sm_this = NULL;

/**
 *  コンストラクタ.
 */
PluginManager::PluginManager()
{
    sm_this = this;
}

/**
 *  デストラクタ.
 */
PluginManager::~PluginManager()
{
    sm_this = nullptr;
}

/**
 *  初期化.
 *  @return trueで初期化成功 falseで失敗.
 */
bool PluginManager::Init()
{

    return true;
}

/**
 *  ファイナライズ.
 *  @return trueでファイナライズ成功 falseで失敗.
 */
bool PluginManager::Final()
{

    return true;
}

/**
 *  プラグインの読み込み.
 *  @return trueで読み込み完了 falseで失敗.
 */
bool PluginManager::LoadPlugins()
{

    return true;
}

/**
 *  プラグインの開放.
 *  @return trueで読み込み完了 falseで失敗.
 */
bool PluginManager::ReleasePlugins()
{

    return true;
}

/**
 *  プラグインオープン.
 *  @param in open_plugin オープンするプラグイン.
 */
void PluginManager::OpenPlugin(IPlugin* open_plugin)
{

}

/**
 *  プラグインクローズ.
 *  @param in open_plugin クローズするプラグイン.
 */
void PluginManager::ClosePlugin(IPlugin* close_plugin)
{
}

/**
 *  メニューウィジェットの追加.
 *  @param in entry_plugin エントリーするプラグイン.
 *  @param in add_widget　 追加するウィジェット.
 *  @param in add_tab_name 追加するタブ.
 */
void PluginManager::AddMenuWidget(const IPlugin* entry_plugin, QWidget *add_widget, const std::string &add_tab_name)
{

}

/**
 *  ツールウィジェットの追加.
 *  @param in entry_plugin エントリーするプラグイン.
 *  @param in add_widget   追加するウィジェット.
 */
void PluginManager::AddToolWidget(const IPlugin* entry_plugin, QWidget* add_widget)
{

}

/**
 *  メッセージの送信.
 *  @param in sender. 送信元プラグイン.
 *  @param in target_plugin_name ターゲットプラグイン名.
 *  @param in message_type メッセージタイプ.
 *  @param in param パラメーター.
 */
bool PluginManager::SendMessage(const IPlugin *sender, const std::string &target_plugin_name, const std::string &message_type, void *param)
{

}

/**
 *  ログ書き込み.
 *  @param in writer 書き込みしたプラグイン.
 *  @param in message メッセージ.
 */
void PluginManager::LogWrite(const std::string &message)
{

}

}       // namesapce meta_tools.
