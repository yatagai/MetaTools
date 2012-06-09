/**
 * ホームメニュープラグインウィジェット.
 * @file home_menu_plugin_widget.cpp.
 * @author yatagai.
 */

#include "home_menu_plugin_widget.h"
#include "home_menu_plugin.h"
#include "ui_home_menu.h"
#include "plugin_manager_widget.h"
#include "../../../main/mainwindow.h"
#include <QtGui>

/**
 * @brief		コンストラクタ.	
 * @author		yatagaik.
 * @param  in	plugin	ホームメニュープラグイン.
 */ 
HomeMenuPluginWidget::HomeMenuPluginWidget(meta_tools::HomeMenuPlugin* plugin) :
    m_plugin(plugin),
    m_ui(new Ui::HomeMenu()),
    m_plugin_manager_widget(new PluginManagerWidget())
{
    m_ui->setupUi(this);
    m_plugin_manager_widget->setWindowFlags(Qt::Tool |
                                     Qt::FramelessWindowHint |
                                     Qt::WindowSystemMenuHint |
                                     Qt::WindowStaysOnTopHint);

    InitMenuButton();
}

/**
  * @brief		デストラクタ.
  * @author		yatagaik.
  */ 
HomeMenuPluginWidget::~HomeMenuPluginWidget()
{
    delete m_ui;
    m_ui = nullptr;

    delete m_plugin_manager_widget;
    m_plugin_manager_widget = nullptr;
}

/**
 * @brief		プラグインの読み込みが完了した.
 * @author		yatagaik.
 * @param  in	plugin	読み込みが完了したプラグイン.
 */
void HomeMenuPluginWidget::OnLoadedPlugin(meta_tools::IPlugin *plugin)
{
    m_plugin_manager_widget->AddPluginWidget(plugin);
}

/**
 * @brief		メニューボタンの初期化.
 * @author		yatagaik.
 */
void HomeMenuPluginWidget::InitMenuButton()
{
    // close button.
    connect(m_ui->AppCloseButton, SIGNAL(clicked()), this, SLOT(OnClickAppCloseButton()));
    // show plugin manager button.
    connect(m_ui->ShowPluginManagerButton, SIGNAL(clicked()), this, SLOT(OnClickShowPluginManagerButton()));
    // show log button.
    connect(m_ui->ShowLogButton, SIGNAL(clicked()), this, SLOT(OnClickShowLogButton()));
}

/**
 * @brief		閉じるボタンが押された.
 * @author		yatagaik.
 */
void HomeMenuPluginWidget::OnClickAppCloseButton()
{
    MainWindow::Order()->close();
}

/**
 * @brief		プラグインマネージャの表示ボタンが押された.
 * @author		yatagaik.
 */
void HomeMenuPluginWidget::OnClickShowPluginManagerButton()
{
    m_plugin_manager_widget->Show();
}

/**
 * @brief		ログ表示ボタンが押された.
 * @author		yatagaik.
 */
void HomeMenuPluginWidget::OnClickShowLogButton()
{
    m_plugin->SendMessage("Log", "LOG_SHOW", nullptr);
}

