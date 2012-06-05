/**
 * ログプラグインクラスの実装.
 * @file log_plugin.cpp.
 * @author yatagai.
 */

#include "log_plugin.h"
#include "ui_log_window.h"
#include <QtGui>

namespace meta_tools
{
/**
 *  コンストラクタ.
 */
LogPlugin::LogPlugin() :
    m_log_window(new QWidget()),
    m_log_window_ui(new Ui::LogWindow())
{
    m_log_window_ui->setupUi(m_log_window);
    AddMessageFunc("LOG_PRINT", &LogPlugin::OnReceiveLogPrint);
}

/**
 *  デストラクタ.
 */
LogPlugin::~LogPlugin()
{
    delete m_log_window_ui;
    m_log_window_ui = nullptr;
    delete m_log_window;
    m_log_window = nullptr;
}

/**
 *  プリント出力メッセージ受信.
 *  @param sender 送り主プラグイン.
 *  @param param 出力文字.
 *  @return trueで正常終了.
 */
bool LogPlugin::OnReceiveLogPrint(const IPlugin *sender, void *param)
{
    const char* add_text = static_cast<const char*>(param);
    m_text += add_text;
    m_log_window_ui->Text->setText(m_text.c_str());
    qDebug() << static_cast<const char*>(add_text);
    return true;
}

/**
 *  プラグインのスタート.
 *  @return trueで正常終了.
 */
bool LogPlugin::OnStart()
{
    AddToolWidget(m_log_window, "Log");
    return true;
}

/**
 *  プラグインの終了.
 *  @return trueで正常終了.
 */
bool LogPlugin::OnClose()
{
    // RemoveToolWidget(log_window);
    return true;
}

}       // namesapce meta_tools.
