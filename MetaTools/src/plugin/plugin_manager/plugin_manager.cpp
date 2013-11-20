/**
 * プラグイン管理クラスの実装.
 * @file plugin_manager.h.
 * @author yatagai.
 */

#include "plugin_manager.h"

#include <QApplication>
#include <QTableWidget>
#include <QMainWindow>
#include <QLayout>
#include "../plugin.h"
#include "../../metatools_tooltip/metatools_tooltip.h"
#include "../../tool_widget_form/tool_widget_form.h"
#include "../build_in_plugin/home_menu_plugin/home_menu_plugin.h"
#include "../build_in_plugin/log_plugin/log_plugin.h"

#include <assert.h>

namespace meta_tools
{
PluginManager* PluginManager::sm_this = NULL;

extern bool AppSendMessage(const IPlugin *sender, const std::string &target_plugin_name, const std::string &message_type, void *param);
extern void AppLogWrite(const IPlugin *writer, const std::string &message);
extern void AppDebugLogWrite(const IPlugin *writer, const std::string &message);
extern void AppAddMenuWidget(const IPlugin *entry_plugin, QWidget *add_widget, const std::string &label, const std::string &add_tab_name);
extern void AppAddToolWidget(const IPlugin *entry_plugin, QWidget *add_widget, const std::string &label);
extern void AppRemoveWidget(const IPlugin *entry_plugin, QWidget *remove_widget);
IPlugin::AppFunctions g_app_functions =
{
    &AppSendMessage,
    &AppLogWrite,
    &AppDebugLogWrite,
    &AppAddMenuWidget,
    &AppAddToolWidget,
    &AppRemoveWidget
};

/**
 *  @brief		コンストラクタ.		
 *  @author		yatagaik.
 *  @param	in	menu_tab	タブメニューウィジェット.
 *  @param	in	main_view	メインタブビュー.
 */ 
PluginManager::PluginManager(QTabWidget *menu_tab, QMainWindow *main_view) :
    m_home_menu_plugin(nullptr),
    m_log_plugin(nullptr),
    m_menu_tab(menu_tab),
    m_main_view(main_view),
    m_plugin_directory((qApp->applicationDirPath() + QDir::separator() + "plugins").toStdString())
{
    sm_this = this;
}

/**
 *  @brief		デストラクタ.
 *  @author     yatagaik.
 */
PluginManager::~PluginManager()
{
    sm_this = nullptr;
}

/**
 *  @brief		初期化.
 *  @author     yatagaik.
 *  @return     trueで初期化成功 falseで失敗.
 */
bool PluginManager::Init()
{
    LoadPlugins();
    return true;
}

/**
 *  @brief		ファイナライズ.
 *  @author     yatagaik.
 *  @return     trueでファイナライズ成功 falseで失敗.
 */
bool PluginManager::Final()
{
    ReleasePlugins();
    return true;
}

/**
 *  @brief		プラグインの読み込み.
 *  @author     yatagaik.
 *  @return     trueで読み込み完了 falseで失敗.
 */
bool PluginManager::LoadPlugins()
{
    // build in pluygin.
    m_plugins.push_back(m_home_menu_plugin = new HomeMenuPlugin(g_app_functions));
    m_plugins.push_back(m_log_plugin = new LogPlugin(g_app_functions));

    // add dynamic plugins.
    typedef IPlugin* (*CreatePlugin)(const IPlugin::AppFunctions& app_functions);
    QDir dynamic_plugin_dir(m_plugin_directory.c_str());
    QStringList file_list = dynamic_plugin_dir.entryList();
    for (int i = 0; i < file_list.count(); ++i)
    {
        if (QLibrary::isLibrary(file_list[i]))
        {
            std::string file_path = m_plugin_directory;
            file_path += QDir::separator().toLatin1();
            file_path += file_list[i].toStdString();
            QLibrary *dynamic_lib = new QLibrary(file_path.c_str());
            dynamic_lib->load();
            CreatePlugin create_func = reinterpret_cast<CreatePlugin>(dynamic_lib->resolve("CreatePlugin"));
            QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
            if (create_func)
            {
                IPlugin* plugin = (*create_func)(g_app_functions);
                assert(plugin);
                std::pair<IPlugin*, QLibrary*> new_pair(plugin, dynamic_lib);
                m_library_list.insert(new_pair);
                m_plugins.push_back(plugin);
            }
            else
            {
                dynamic_lib->unload();
                delete dynamic_lib;
            }
            QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
        }
    }

    // load log print & regist plugin manager widget.
    for(auto it = m_plugins.begin(); it != m_plugins.end(); ++it)
    {
        LogWrite("[PluginManager] load plugin " + std::string((*it)->GetName()) + "\n");        // load log print.
        SendMessage(nullptr, m_home_menu_plugin->GetName(), "LOADED_PLUGIN", *it);              // regist plugin manager widget.
        QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
    }

    // open start up.
    for(auto it = m_plugins.begin(); it != m_plugins.end(); ++it)
    {
        if ((*it)->IsStartUp())
        {
            OpenPlugin(*it);
            QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
        }
    }

    return true;
}

/**
 *  @brief		プラグインの開放.
 *  @author     yatagaik.
 *  @return     trueで読み込み完了 falseで失敗.
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
        QLibrary *library = m_library_list[*it];
        delete (*it);
        QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
        if (library)
        {
            // library->unload();
            // delete library;
        }
    }
    m_plugins.empty();
    m_library_list.empty();
    m_home_menu_plugin = nullptr;
    m_log_plugin = nullptr;
    return true;
}

/**
 *  @brief		プラグインオープン.
 *  @author     yatagaik.
 *  @param  in  open_plugin オープンするプラグイン.
 */
void PluginManager::OpenPlugin(IPlugin *open_plugin)
{
    open_plugin->Start();
}

/**
 *  @brief		プラグインクローズ.
 *  @author     yatagaik.
 *  @param  in  open_plugin クローズするプラグイン.
 */
void PluginManager::ClosePlugin(IPlugin *close_plugin)
{
    if (close_plugin->Closing())
    {
        close_plugin->Close();
    }
}

/**
 *  @brief		メニューウィジェットの追加.
 *  @author     yatagaik.
 *  @param  in  entry_plugin エントリーするプラグイン.
 *  @param  in  add_widget　 追加するウィジェット.
 *  @param  in  label        追加するウィジェットのラベル.
 *  @param  in  add_tab_name 追加するタブ.
 */
void PluginManager::AddMenuWidget(const IPlugin * entry_plugin, QWidget *add_widget, const std::string &label, const std::string &/*add_tab_name*/)
{
    MetaToolsToolTip* new_tool_tip = new MetaToolsToolTip(static_cast<QWidget*>(m_menu_tab->widget(0)), entry_plugin);
    new_tool_tip->SetChildWidget(add_widget);
    new_tool_tip->SetLabel(label.c_str());
}

/**
 *  @brief		ツールウィジェットの追加.
 *  @author     yatagaik.
 *  @param  in  entry_plugin エントリーするプラグイン.
 *  @param  in  add_widget   追加するウィジェット.
 *  @param  in  label        追加するウィジェットのラベル.
 */
void PluginManager::AddToolWidget(const IPlugin * entry_plugin, QWidget* add_widget, const std::string &label)
{
    ToolWidgetForm *new_tool_widget = new ToolWidgetForm(entry_plugin, m_main_view);
    new_tool_widget->SetChildWidget(add_widget);

    new_tool_widget->setWindowTitle(label.c_str());

    if (std::strcmp(entry_plugin->GetName(), "Log") == 0)
    {
        m_main_view->addDockWidget(Qt::BottomDockWidgetArea, new_tool_widget, Qt::Horizontal);
    }
    else
    {
        m_main_view->addDockWidget(Qt::TopDockWidgetArea, new_tool_widget, Qt::Horizontal);
    }
    m_tool_windows.push_back(new_tool_widget);
}

/**
 *  @brief		ウィジェットの削除.
 *  @author		yatagaik.
 *  @param  in  remove_widget 削除するウィジェット.
 */
void PluginManager::RemoveWidget(const IPlugin * /*entry_plugin*/, QWidget *remove_widget)
{
    // ツールウィジェットから検索.
    std::vector<QWidget*>::iterator it = m_tool_windows.begin();
    for (; it != m_tool_windows.end(); ++it)
    {
        ToolWidgetForm *form = dynamic_cast<ToolWidgetForm*>(*it);
        if (!form)
        {
            continue;
        }
        if (form && form->GetChildWidget() == remove_widget)
        {
            // ToolTipの削除.
            it = m_tool_windows.erase(it);
            form->SetChildWidget(nullptr);
            delete form;
            return;
        }
    }

    // メニューウィジェットから検索.
    for (int i = 0; i < m_menu_tab->count(); ++i)
    {
        QWidget *tab = dynamic_cast<QWidget*>(m_menu_tab->widget(i));
        if (!tab)
        {
            continue;
        }
        for (int j = 0; j < tab->children().count(); ++j)
        {
            MetaToolsToolTip *tool_tip = dynamic_cast<MetaToolsToolTip*>(tab->children().at(j));
            if (tool_tip && tool_tip->GetChildWidget() == remove_widget)
            {
                // ToolTipの削除.
                tool_tip->SetChildWidget(nullptr);
                delete tool_tip;
                // タブが空になったらタブごと削除(ホームは例外).
                if (tab->children().count() == 0 && i != 0)
                {
                    delete tab;
                }
                return;
            }
        }
    }
}

/**
 *  @brief		メッセージの送信.
 *  @author     yatagaik.
 *  @param  in  sender. 送信元プラグイン.
 *  @param  in  target_plugin_name ターゲットプラグイン名.
 *  @param  in  message_type メッセージタイプ.
 *  @param  in  param パラメーター.
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
 *  @brief		ログ書き込み.
 *  @author     yatagaik.
 *  @param  in  message メッセージ.
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
 *  @brief		プラグインの検索.
 *  @author     yatagaik.
 *  @param  in  plugin_name プラグイン名.
 *  @return     見つかればプラグインポインタ 見つからなければnullptr
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
