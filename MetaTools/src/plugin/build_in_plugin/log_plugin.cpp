/**
 * ログプラグインクラスの実装.
 * @file log_plugin.cpp.
 * @author yatagai.
 */

#include "log_plugin.h"

namespace meta_tools
{
/**
 *  コンストラクタ.
 */
LogPlugin::LogPlugin()
{
    AddMessageFunc("LOG_PRINT", &LogPlugin::OnReceiveLogPrint);
}

/**
 *  デストラクタ.
 */
LogPlugin::~LogPlugin()
{

}

/**
 *  プリント出力メッセージ受信.
 *  @param sender 送り主プラグイン.
 *  @param param 出力文字.
 *  @return trueで正常終了.
 */
bool LogPlugin::OnReceiveLogPrint(const IPlugin *sender, void *param)
{
    return true;
}

/**
 *  プラグインのスタート.
 *  @return trueで正常終了.
 */
bool LogPlugin::OnStart()
{

    return true;
}

/**
 *  プラグインの終了.
 *  @return trueで正常終了.
 */
bool LogPlugin::OnClose()
{

    return true;
}

}       // namesapce meta_tools.
