/**
 * メインウインドウクラスの実装.
 * @file mainwindow.cpp.
 * @author yatagai.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolButton>
#include <QMainWindow>
#include <QDockWidget>
#include <QMessageBox>
#include <qevent.h>

#include "../save_load/save_load.h"
#include "../plugin/plugin_manager/plugin_manager.h"
#include "../tool_widget_form/tool_widget_form.h"

namespace
{

const float MENU_MINIZATION_SWITCH_SIZE(12.0f);
const float MENU_MINIMUM_HEIGHT(23.0f);
const float MENU_MAXIMUM_HEIGHT(80.0f);

const int MENU_ANIMATE_DELTA(10);                   // animate delta
const float MENU_ANIMATE_SPEED(10.0);               // animate speed MENU_ANIMATE_DELTA/ms.

}
MainWindow* MainWindow::sm_this = nullptr;

/**
 *  @brief      コンストラクタ.
 *  @author		yatagaik.
 *  @param  in  parent 親ウィジェット.
 */
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow),
    m_main_view(nullptr),
    m_is_menu_minization(false),
    m_save_load(nullptr),
    m_plugin_manager(nullptr)
{
    sm_this = this;
    ui->setupUi(this);
    ui->menu->setMinimumHeight(MENU_MAXIMUM_HEIGHT);
    ui->menu->setMaximumHeight(MENU_MAXIMUM_HEIGHT);

    m_main_view = new QMainWindow(this);
    m_main_view->setWindowFlags(Qt::Widget);
    layout()->addWidget(m_main_view);
    m_main_view->setDockNestingEnabled(true);
}

/**
 *  @brief      デストラクタ.
 *  @author		yatagaik.
 */
MainWindow::~MainWindow()
{
    // finalize plugins.
    FinalizePlugins();

    // save windows info.
    meta_tools::SaveLoad::Order()->SetAppSaveData("main_window_is_maximized", QJsonValue(isMaximized()));
    meta_tools::SaveLoad::Order()->SetAppSaveData("main_window_is_menu_minization", QJsonValue(m_is_menu_minization));

    // finalize saveload.
    FinalizeSaveLoad();

    // delete ui.
    sm_this = nullptr;
    delete ui;
}

/**
 *  @brief      初期化.
 *  @author		yatagaik.
 */
void MainWindow::Initilize()
{
    // initialize saveload.
    InitializeSaveLoad();

    // add menu_minimization_switch.
    CreateMenuMinimizationSwitch();

    // initialize plugins.
    InitializePlugins();

    // load window info.
    QJsonValue main_window_is_menu_minization = meta_tools::SaveLoad::Order()->GetAppSaveData("main_window_is_menu_minization");
    if (main_window_is_menu_minization.isBool() && main_window_is_menu_minization.toBool())
    {
        m_is_menu_minization = true;
        ui->menu->setMinimumHeight(MENU_MINIMUM_HEIGHT);
        ui->menu->setMaximumHeight(MENU_MINIMUM_HEIGHT);
    }
}

/**
 *  @brief      表示.
 *  @author		yatagaik.
 */
void MainWindow::Show()
{
    QJsonValue main_window_is_maximized = meta_tools::SaveLoad::Order()->GetAppSaveData("main_window_is_maximized");
    if (main_window_is_maximized.isBool() && main_window_is_maximized.toBool())
    {
        showMaximized();
    }
    else
    {
        show();
    }
}

/**
 *  @brief      メニュー最小化スイッチ作成.
 *  @author		yatagaik.
 */
void MainWindow::CreateMenuMinimizationSwitch()
{
    QToolButton *menu_minimization_switch_button = new QToolButton(ui->menu);
    menu_minimization_switch_button->setCursor(Qt::ArrowCursor);
    menu_minimization_switch_button->setAutoRaise(true);
    menu_minimization_switch_button->setIcon(QIcon(":/metatools_resource/img/arrow_two_head_v.png"));
    menu_minimization_switch_button->setIconSize(QSize(MENU_MINIZATION_SWITCH_SIZE, MENU_MINIZATION_SWITCH_SIZE));
    ui->menu->setCornerWidget(menu_minimization_switch_button, Qt::TopRightCorner);

    // set event.
    connect(menu_minimization_switch_button, SIGNAL(clicked()), SLOT(OnMinimizationSwitch()));
    connect(&m_menu_animate_timer, SIGNAL(timeout()), SLOT(MenuMinimizationSwitchAnimation()));
}

/**
 *  @brief      メニューの最小化スイッチの開始.
 *  @author		yatagaik.
 */
void MainWindow::OnMinimizationSwitch()
{
    m_is_menu_minization = !m_is_menu_minization;

    if (!m_menu_animate_timer.isActive())
    {
        m_menu_animate_timer.start(MENU_ANIMATE_DELTA);
    }
}

/**
 *  @brief      メニュー最小化スイッチアニメーション.
 *  @author		yatagaik.
 */
void MainWindow::MenuMinimizationSwitchAnimation()
{
    float set_height = ui->menu->minimumHeight();
    bool animation_end = false;

    if (m_is_menu_minization)
    {
        // 最小化サイズ計算.
        set_height -= MENU_ANIMATE_SPEED;
        if (set_height <= MENU_MINIMUM_HEIGHT)
        {
            set_height = MENU_MINIMUM_HEIGHT;
            animation_end = true;
        }
    }
    else
    {
        // 最大化サイズ計算.
        set_height += MENU_ANIMATE_SPEED;
        if (set_height >= MENU_MAXIMUM_HEIGHT)
        {
            set_height = MENU_MAXIMUM_HEIGHT;
            animation_end = true;
        }
    }

    ui->menu->setMinimumHeight(set_height);
    ui->menu->setMaximumHeight(set_height);

    if (animation_end)
    {
        // アニメーション終了.
        m_menu_animate_timer.stop();
    }
}

/**
 *  @brief      SaveLoadの初期化.
 *  @author		yatagaik.
 */
void MainWindow::InitializeSaveLoad()
{
    m_save_load = new meta_tools::SaveLoad();
}

/**
 *  @brief      SaveLoadの破棄.
 *  @author		yatagaik.
 */
void MainWindow::FinalizeSaveLoad()
{
    if (m_save_load)
    {
        delete m_save_load;
        m_save_load = nullptr;
    }
}

/**
 *  @brief      プラグインの初期化.
 *  @author		yatagaik.
 */
void MainWindow::InitializePlugins()
{
    m_plugin_manager = new meta_tools::PluginManager(ui->menu, m_main_view);
    m_plugin_manager->Init();
}

/**
 *  @brief      プラグインの破棄.
 *  @author		yatagaik.
 */
void MainWindow::FinalizePlugins()
{
    if (m_plugin_manager)
    {
        m_plugin_manager->Final();
        delete m_plugin_manager;
        m_plugin_manager = nullptr;
    }
}

/**
 *  @brief      閉じるイベント.
 *  @author		yatagaik.
 */
void MainWindow::closeEvent(QCloseEvent *close_event)
{
    QMessageBox::StandardButton ret = QMessageBox::question(
        this,
        QString::fromLocal8Bit("MetaTools"),
        QString::fromLocal8Bit("MetaToolsを終了しますか?"), QMessageBox::Yes | QMessageBox::No);
    if (ret != QMessageBox::Yes)
    {
        close_event->ignore();
    }
}
