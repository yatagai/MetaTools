/**
 * プラグイン管理クラスの定義.
 * @file plugin_manager.h.
 * @author yatagai.
 */
#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include <vector>
#include <string>

class QWidget;

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
    PluginManager();
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

    // プラグイン関係.
public:
    struct PluginWidgetInfo
    {
        QWidget* wiget;
        IPlugin* owner;
    };
public:
    void OpenPlugin(IPlugin* open_plugin);
    void ClosePlugin(IPlugin* close_plugin);
    void AddMenuWidget(const IPlugin* entry_plugin, QWidget *add_widget, const std::string &add_tab_name);
    void AddToolWidget(const IPlugin* entry_plugin, QWidget* add_widget);
    bool SendMessage(const IPlugin *sender, const std::string &target_plugin_name, const std::string &message_type, void *param);
    void LogWrite(const std::string &message);

private:
    std::vector<IPlugin*> m_plugins;
    std::vector<PluginWidgetInfo> m_menu_widget;
    std::vector<PluginWidgetInfo> m_tool_widget;
};

}       // namespace meta_tools.

#endif  // PLUGIN_MANAGER_H
