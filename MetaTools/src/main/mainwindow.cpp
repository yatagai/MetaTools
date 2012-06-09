/**
 * メインウインドウクラスの実装.
 * @file mainwindow.cpp.
 * @author yatagai.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolButton>

#include "../plugin/plugin_manager/plugin_manager.h"
#include "../tool_widget_form/tool_widget_form.h"

namespace
{

const float MENU_MINIZATION_SWITCH_SIZE(15.0f);
const float MENU_MINIMUM_HEIGHT(22.0f);
const float MENU_MAXIMUM_HEIGHT(80.0f);

const int MENU_ANIMATE_DELTA(10);                   // animate delta
const float MENU_ANIMATE_SPEED(10.0);               // animate speed MENU_ANIMATE_DELTA/ms.

}
MainWindow* MainWindow::sm_this = NULL;

/**
 *  @brief      コンストラクタ.
 *  @author		yatagaik.
 *  @param  in  parent 親ウィジェット.
 */
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow),
    m_is_menu_minization(false),
    m_plugin_manager(nullptr)
{
    sm_this = this;
    ui->setupUi(this);

    // add menu_minimization_switch.
    CreateMenuMinimizationSwitch();

    // initialize plugins.
    InitializePlugins();
}

/**
 *  @brief      デストラクタ.
 *  @author		yatagaik.
 */
MainWindow::~MainWindow()
{
    // finalize plugins.
    FinalizePlugins();

    // delete ui.
    sm_this = nullptr;
    delete ui;
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
    ui->menu->setDocumentMode(m_is_menu_minization);

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
 *  @brief      プラグインの初期化.
 *  @author		yatagaik.
 */
void MainWindow::InitializePlugins()
{
    connect(ui->main_view, SIGNAL(tabCloseRequested(int)), this, SLOT(OnClickToolWidgetCloseButton(int)));
    m_plugin_manager = new meta_tools::PluginManager(ui->menu, ui->main_view);
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
 *  @brief      ツールウィジェットの閉じるボタンが押された.
 *  @author		yatagaik.
 *  @param  in  index クリックされたウィジェットのインデックス.
 */
void MainWindow::OnClickToolWidgetCloseButton(int index)
{
    meta_tools::ToolWidgetForm *tool_widget_form = dynamic_cast<meta_tools::ToolWidgetForm*>(ui->main_view->widget(index));
    if (tool_widget_form)
    {
        tool_widget_form->OnClickCloseButton();
    }
}
