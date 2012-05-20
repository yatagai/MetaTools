/**
 * ホームメニュープラグイン.
 * @file plugin_manager.h.
 * @author yatagai.
 */

#include "home_menu_plugin.h"

namespace meta_tools
{
/**
 *  コンストラクタ.
 */
HomeMenuPlugin::HomeMenuPlugin()
{

}

/**
 *  デストラクタ.
 */
HomeMenuPlugin::~HomeMenuPlugin()
{

}

/**
 *  プラグインのスタート.
 *  @return trueで正常終了.
 */
bool HomeMenuPlugin::OnStart()
{

    return true;
}

/**
 *  プラグインの終了.
 *  @return trueで正常終了.
 */
bool HomeMenuPlugin::OnClose()
{

    return true;
}

}       // namesapce meta_tools.
