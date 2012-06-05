/**
 * プラグイン管理クラスの実装.
 * @file plugin_manager.h.
 * @author yatagai.
 */

#include "plugin_manager.h"

#include <QTableWidget>
#include "../../metatools_tooltip/metatools_tooltip.h"
#include "../build_in_plugin/home_menu_plugin.h"
#include "../build_in_plugin/log_plugin.h"

namespace meta_tools
{
PluginManager* PluginManager::sm_this = NULL;

/**
 *  コンストラクタ.
 */
PluginManager::PluginManager(QTabWidget *menu_tab, QTabWidget *main_view) :
    m_log_plugin(nullptr),
    m_menu_tab(menu_tab),
    m_main_view(main_view)
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
    LoadPlugins();
    return true;
}

/**
 *  ファイナライズ.
 *  @return trueでファイナライズ成功 falseで失敗.
 */
bool PluginManager::Final()
{
    ReleasePlugins();
    return true;
}

/**
 *  プラグインの読み込み.
 *  @return trueで読み込み完了 falseで失敗.
 */
bool PluginManager::LoadPlugins()
{
    // build in pluygin.
    m_plugins.push_back(new HomeMenuPlugin());
    m_plugins.push_back(m_log_plugin = new LogPlugin());

    // add dynamic plugins.


    // load plugins print.
    for(auto it = m_plugins.begin(); it != m_plugins.end(); ++it)
    {
        LogWrite("[PluginManager] load plugin " + std::string((*it)->GetName()) + "\n");
    }

    // open start up.
    for(auto it = m_plugins.begin(); it != m_plugins.end(); ++it)
    {
        if ((*it)->IsStartUp())
        {
            OpenPlugin(*it);
        }
    }

    return true;
}

/**
 *  プラグインの開放.
 *  @return trueで読み込み完了 falseで失敗.
 */
bool PluginManager::ReleasePlugins()
{
    // close and delete.
    for(auto it = m_plugins.begin(); it != m_plugins.end(); ++it)
    {
        if ((*it)->IsExecute())
        {
            ClosePlugin(*it);
        }
        delete (*it);
    }
    m_plugins.empty();
    m_log_plugin = nullptr;
    return true;
}

/**
 *  プラグインオープン.
 *  @param in open_plugin オープンするプラグイン.
 */
void PluginManager::OpenPlugin(IPlugin* open_plugin)
{
    open_plugin->OnStart();
}

/**
 *  プラグインクローズ.
 *  @param in open_plugin クローズするプラグイン.
 */
void PluginManager::ClosePlugin(IPlugin* close_plugin)
{
    if (close_plugin->OnClosing())
    {
        close_plugin->Close();
    }
}

/**
 *  メニューウィジェットの追加.
 *  @param in entry_plugin エントリーするプラグイン.
 *  @param in add_widget　 追加するウィジェット.
 *  @param in label        追加するウィジェットのラベル.
 *  @param in add_tab_name 追加するタブ.
 */
void PluginManager::AddMenuWidget(const IPlugin* entry_plugin, QWidget *add_widget, const std::string &label, const std::string &add_tab_name)
{
    MetaToolsToolTip* new_tool_tip = new MetaToolsToolTip(static_cast<QWidget*>(m_menu_tab->children().at(0)));
    new_tool_tip->SetChildWidget(add_widget);
    new_tool_tip->SetLabel(label.c_str());
}

/**
 *  ツールウィジェットの追加.
 *  @param in entry_plugin エントリーするプラグイン.
 *  @param in add_widget   追加するウィジェット.
 *  @param in label        追加するウィジェットのラベル.
 */
void PluginManager::AddToolWidget(const IPlugin* entry_plugin, QWidget* add_widget, const std::string &label)
{
    m_main_view->addTab(add_widget, label.c_str());
}

/**
 *  メニューウィジェットの削除.
 *  @param in remove_widget 削除するウィジェット.
 */
void PluginManager::RemoveMenuWidget(QWidget *remove_widget)
{

}

/**
 *  ツールウィジェットの削除.
 *  @param in remove_widget 削除するウィジェット.
 */
void PluginManager::RemoveToolWidget(QWidget *remove_widget)
{
    int index = m_main_view->indexOf(remove_widget);
    if (index >= 0)
    {
        m_main_view->removeTab(index);
    }
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
    IPlugin* plugin = Find(target_plugin_name);
    if (plugin)
    {
        return plugin->ReceiveMessage(sender, message_type, param);
    }

    // not found.
    if (sender)
    {
        sender->LogWriteLine("SendMessage not found plugin " + target_plugin_name);
    }
    else
    {
        LogWrite("[PluginManager] SendMessage not found plugin " + target_plugin_name + "\n");
    }

    return false;
}

/**
 *  ログ書き込み.
 *  @param in writer 書き込みしたプラグイン.
 *  @param in message メッセージ.
 */
void PluginManager::LogWrite(const std::string &message)
{
    if (m_log_plugin)
    {
        void* param = reinterpret_cast<void*>(const_cast<char*>(message.c_str()));
        m_log_plugin->ReceiveMessage(nullptr, "LOG_PRINT", param);
    }
}

/**
 *  プラグインの検索.
 *  @param in plugin_name プラグイン名.
 *  @return 見つかればプラグインポインタ 見つからなければnullptr
 */
IPlugin* PluginManager::Find(const std::string &plugin_name)
{
    for(auto it = m_plugins.begin(); it != m_plugins.end(); ++it)
    {
        if ((*it)->GetName() == plugin_name)
        {
            return *it;
        }
    }

    return nullptr;
}

}       // namesapce meta_tools.
