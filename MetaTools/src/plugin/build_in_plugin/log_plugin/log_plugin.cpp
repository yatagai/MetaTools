/**
 * ログプラグインクラスの実装.
 * @file log_plugin.cpp.
 * @author yatagai.
 */

#include "log_plugin.h"
#include "ui_log_window.h"
#include <QtGui>
#include <QIcon>

namespace meta_tools
{

/**
 *  @brief		コンストラクタ.		
 *  @author		yatagaik.
 */ 
LogPlugin::LogPlugin(const AppFunctions &app_functions) :
    IPlugin(app_functions),
    m_log_window(new QWidget()),
    m_log_window_ui(new Ui::LogWindow()),
    m_ishide(true)
{
    m_log_window_ui->setupUi(m_log_window);
    AddMessageFunc("LOG_PRINT", &LogPlugin::OnReceiveLogPrint);
    AddMessageFunc("LOG_SHOW", &LogPlugin::OnReceiveLogShow);
    m_widget_icon->addFile(":/metatools_resource/img/log_icon.png");
}

/**
 *  @brief		デストラクタ.		
 *  @author		yatagaik.
 */ 
LogPlugin::~LogPlugin()
{
    delete m_log_window_ui;
    m_log_window_ui = nullptr;
    delete m_log_window;
    m_log_window = nullptr;
}

/**
 *  @brief		プリント出力メッセージ受信.
 *  @author		yatagaik.
 *  @param	in	sender 送り主プラグイン.
 *  @param	in	param 出力文字.
 *  @return		trueで正常終了.
 */
bool LogPlugin::OnReceiveLogPrint(const IPlugin * /*sender*/, void *param)
{
    const char* add_text = static_cast<const char*>(param);
    m_text += add_text;
    m_log_window_ui->Text->setText(QString::fromLocal8Bit(m_text.c_str()));
    qDebug() << add_text;
    return true;
}

/**
 *  @brief		表示メッセージ受信.
 *  @author		yatagaik.
 *  @param	in	sender 送り主プラグイン.
 *  @param	in	param 出力文字.
 *  @return		trueで正常終了.
 */
bool LogPlugin::OnReceiveLogShow(const IPlugin * /*sender*/, void * /*param*/)
{
    if (m_ishide)
    {
        AddToolWidget(m_log_window, "Log");
        m_ishide = false;
    }
    else if (m_log_window->parentWidget())
    {
        m_log_window->parentWidget()->focusWidget();
    }
    return true;
}

/**
 *  @brief      閉じるボタンが押された.
 *  @author		yatagaik.
 *  @param  in	clicked_widget	クリックされたウィジェット.
 */
void LogPlugin::OnClickCloseButton(QWidget *clicked_widget, bool &/*cancel*/)
{
    if (m_log_window == clicked_widget)
    {
        if (!m_ishide)
        {
            m_ishide = true;
        }
    }
}

/**
 *  @brief		プラグインのスタート.		
 *  @author		yatagaik.
 *  @return		trueで正常終了.
 */ 
bool LogPlugin::OnStart()
{
    if (m_ishide)
    {
        AddToolWidget(m_log_window, "Log");
        m_ishide = false;
    }
    return true;
}

/**
 *  @brief		プラグインの終了.
 *  @author		yatagaik.
 *  @return		trueで正常終了.
 */
bool LogPlugin::OnClose()
{
    if (!m_ishide)
    {
        RemoveWidget(m_log_window);
        m_ishide = true;
    }
    return true;
}

}       // namesapce meta_tools.
