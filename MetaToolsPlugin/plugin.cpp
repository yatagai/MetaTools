/**
 * プラグインのインターフェースの実装.
 * @file plugin.cpp.
 * @author yatagai.
 */

#include "plugin.h"
#include <QtGui>
#include <QIcon>

namespace meta_tools
{
extern bool AppSendMessage(const IPlugin *sender, const std::string &target_plugin_name, const std::string &message_type, void *param);
extern void AppLogWrite(const IPlugin *writer, const std::string &message);
extern void AppDebugLogWrite(const IPlugin *writer, const std::string &message);
extern void AppAddMenuWidget(const IPlugin *entry_plugin, QWidget *add_widget, const std::string &label, const std::string &add_tab_name);
extern void AppAddToolWidget(const IPlugin *entry_plugin, QWidget *add_widget, const std::string &label);
extern void AppRemoveWidget(const IPlugin *entry_plugin, QWidget *add_widget);

/**
 *  @brief		コンストラクタ.
 *  @author		yatagaik.
 */ 
IPlugin::IPlugin() :
    m_widget_icon(new QIcon()),
    m_is_execute(false)
{
}

/**
 *  @brief		デストラクタ.
 *  @author		yatagaik.
 */ 
IPlugin::~IPlugin()
{
    if (m_widget_icon)
    {
        delete m_widget_icon;
        m_widget_icon = nullptr;
    }
}

/**
 *  @brief		プラグインの開始.
 *  @author		yatagaik.
 *  @return		trueで成功 falseで失敗.
 */ 
bool IPlugin::Start()
{
    if (OnStart())
    {
        m_is_execute = true;
    }
    return m_is_execute;
}

/**
 *  @brief		プラグインの終了してもよいか.
 *  @author		yatagaik.
 *  @return     trueで終了してもよい falseで終了したらダメ.
 */
bool IPlugin::Closing()
{
    return OnClosing();
}

/**
 *  @brief		プラグインの終了.
 *  @author		yatagaik.
 *  @return     trueで成功 falseで失敗.
 */
bool IPlugin::Close()
{
    if (OnClose())
    {
        m_is_execute = false;
    }

    return !m_is_execute;
}

/**
 *  @brief		プラグインにメッセージ送信.
 *  @author		yatagaik.
 *  @param  in  target_plugin_name 送信先のプラグイン名.
 *  @param  in  message_type メッセージタイプ.
 *  @param  in  param パラメータ.
 */
bool IPlugin::SendMessage(const std::string &target_plugin_name, const std::string &message_type, void *param) const
{
    return AppSendMessage(this, target_plugin_name, message_type, param);
}

/**
 *  @brief		ログプラグイン.
 *  @author		yatagaik.
 *  @param  in  sender 送り主プラグイン.
 *  @param  in  message_type メッセージタイプ.
 *  @param  in  param パラメータ.
 *  @return     trueで処理した falseで処理していない.
 */
bool IPlugin::ReceiveMessage(const IPlugin *sender, const std::string &message_type, void *param)
{
    auto it = m_message_functions.find(message_type);
    if (it != m_message_functions.end())
    {
        return it->second(sender, param);
    }
    return false;
}

/**
 *  @brief		ログに出力.
 *  @author		yatagaik.
 *  @param  in  message 出力するメッセージ.
 */
void IPlugin::LogWrite(const std::string &message) const
{
    AppLogWrite(this, message);
}

/**
 *  @brief		ログに1行出力.
 *  @author		yatagaik.
 *  @param  in  message 出力するメッセージ.
 */
void IPlugin::LogWriteLine(const std::string &message) const
{
    AppLogWrite(this, message + "\n");
}

/**
 *  @brief		デバッグ用ログに出力.
 *  @author		yatagaik.
 *  @param  in  message 出力するメッセージ.
 */
void IPlugin::DebugLogWrite(const std::string &message) const
{
    AppDebugLogWrite(this, message);
}

/**
 *  @brief		デバッグ用ログに1行出力.
 *  @author		yatagaik.
 *  @param  in  message 出力するメッセージ.
 */
void IPlugin::DebugLogWriteLine(const std::string &message) const
{
    AppDebugLogWrite(this, message + "\n");
}

/**
 *  @brief		メニュー用Widget追加.
 *  @author		yatagaik.
 *  @param  in  add_widget 追加するWidget.
 *  @param  in  label 追加するWidgetのラベル.
 *  @param  in  add_tab_name 追加するタブ.
 */
void IPlugin::AddMenuWidget(QWidget *add_widget, const std::string &label, const std::string &add_tab_name)
{
    AppAddMenuWidget(this, add_widget, label, add_tab_name);
}

/**
 *  @brief		ツール用Widget追加.
 *  @author		yatagaik.
 *  @param  in  add_widget 追加するWidget.
 *  @param  in  label 追加するWigetのラベル.
 */
void IPlugin::AddToolWidget(QWidget *add_widget, const std::string &label)
{
    AppAddToolWidget(this, add_widget, label);
}

/**
 *  @brief		ウィジェットの削除.
 *  @author		yatagaik.
 *  @param  in	remove_widget	削除するウィジェット.
 */ 
void IPlugin::RemoveWidget(QWidget *remove_widget)
{
    AppRemoveWidget(this, remove_widget);
}

}   // end namesapce meta_tools
