/**
 * ホームメニュープラグイン.
 * @file plugin_manager.h.
 * @author yatagai.
 */

#include "home_menu_plugin.h"
#include "ui_home_menu.h"
#include <QtGui>

namespace meta_tools
{
/**
 *  コンストラクタ.
 */
HomeMenuPlugin::HomeMenuPlugin() :
    m_home_menu(new QWidget()),
    m_home_menu_ui(new Ui::HomeMenu())
{
    m_home_menu_ui->setupUi(m_home_menu);
}

/**
 *  デストラクタ.
 */
HomeMenuPlugin::~HomeMenuPlugin()
{
    delete m_home_menu_ui;
    m_home_menu_ui = nullptr;
    delete m_home_menu;
    m_home_menu = nullptr;
}

/**
 *  プラグインのスタート.
 *  @return trueで正常終了.
 */
bool HomeMenuPlugin::OnStart()
{
    AddMenuWidget(m_home_menu, "MetaTools", "ホーム");
    return true;
}

/**
 *  プラグインの終了.
 *  @return trueで正常終了.
 */
bool HomeMenuPlugin::OnClose()
{
    // RemoveMenuWidget(m_home_menu);
    return true;
}

}       // namesapce meta_tools.
