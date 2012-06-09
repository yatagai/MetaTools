/**
 * ホームメニュープラグイン.
 * @file home_menu_plugin.cpp.
 * @author yatagai.
 */

#include "home_menu_plugin.h"
#include "home_menu_plugin_widget.h"
#include <QIcon>
namespace meta_tools
{

/**
 *  @brief      コンストラクタ.
 *  @author		yatagaik.
 */
HomeMenuPlugin::HomeMenuPlugin() :
    m_home_menu_widget(new HomeMenuPluginWidget(this))
{
    AddMessageFunc("LOADED_PLUGIN", &HomeMenuPlugin::OnLoadedPluginMessage);
    m_widget_icon->addFile(":/metatools_resource/img/home_icon.png");
}

/**
 *  @brief      デストラクタ.
 *  @author		yatagaik.
 */
HomeMenuPlugin::~HomeMenuPlugin()
{
    delete m_home_menu_widget;
    m_home_menu_widget = nullptr;
}

/**
 *  @brief      閉じるボタンが押された.
 *  @author		yatagaik.
 *  @param  in	clicked_widget	クリックされたウィジェット.
 */
void HomeMenuPlugin::OnClickCloseButton(QWidget *clicked_widget)
{
    if (m_home_menu_widget == clicked_widget)
    {
        m_home_menu_widget->OnClickAppCloseButton();
    }
}

/**
 *  @brief      プラグインのスタート.
 *  @author		yatagaik.
 *  @return     trueで正常終了.
 */
bool HomeMenuPlugin::OnStart()
{
    AddMenuWidget(m_home_menu_widget, "MetaTools", "ホーム");
    return true;
}

/**
 *  @brief      プラグインの終了.
 *  @author		yatagaik.
 *  @return     trueで正常終了.
 */
bool HomeMenuPlugin::OnClose()
{
    RemoveWidget(m_home_menu_widget);
    return true;
}

/**
 *  @brief		プラグインの読み込みが完了した.
 *  @author		yatagaik.
 *  @param  in	plugin	読み込みが完了したプラグイン.
 */
bool HomeMenuPlugin::OnLoadedPluginMessage(const IPlugin * /*sender*/, void *param)
{
    if (param != nullptr)
    {
        IPlugin* plugin = reinterpret_cast<IPlugin*>(param);
        m_home_menu_widget->OnLoadedPlugin(plugin);
    }
    return true;
}

}       // namesapce meta_tools.
