/**
 * プラグイン管理クラスの定義.
 * @file plugin_manager.h.
 * @author yatagai.
 */
#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include <vector>
#include <map>
#include <string>

class QWidget;
class QTabWidget;
class QLibrary;
namespace meta_tools
{
class IPlugin;

/**
 *  プラグイン管理クラス.
 *  @author yatagai.
 */
class PluginManager
{
public:
    explicit PluginManager(QTabWidget *menu_tab, QTabWidget *main_view);
    ~PluginManager();

    // シングルトン.
public:
    static PluginManager* Order()
    {
        return sm_this;
    }
private:
    static PluginManager *sm_this;

    // 初期化/終了処理関係.
public:
    bool Init();
    bool Final();
private:
    bool LoadPlugins();
    bool ReleasePlugins();

public:    
    // widgetの追加&削除.
    void AddMenuWidget(const IPlugin* entry_plugin, QWidget *add_widget, const std::string &label, const std::string &add_tab_name);
    void AddToolWidget(const IPlugin* entry_plugin, QWidget* add_widget, const std::string &label);
    void RemoveWidget(const IPlugin* entry_plugin, QWidget *remove_widget);

    // メッセージの送信.
    bool SendMessage(const IPlugin *sender, const std::string &target_plugin_name, const std::string &message_type, void *param);

    // ログの書き込み.
    void LogWrite(const std::string &message);

    // オープン&クローズ.
    void OpenPlugin(IPlugin* open_plugin);
    void ClosePlugin(IPlugin* close_plugin);

private:
    // プラグインの検索.
    IPlugin* Find(const std::string &plugin_name);
private:
    std::vector<IPlugin*> m_plugins;
    std::map<IPlugin*, QLibrary*> m_library_list;
    IPlugin *m_home_menu_plugin;
    IPlugin *m_log_plugin;
    QTabWidget *m_menu_tab;
    QTabWidget *m_main_view;

    // プラグインディレクトリ.
private:
    std::string m_plugin_directory;
};

}       // namespace meta_tools.

#endif  // PLUGIN_MANAGER_H
