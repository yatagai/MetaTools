/**
 * メインウインドウクラスの定義.
 * @file mainwindow.h.
 * @author yatagai.
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class MainWindow;
}
class QMainWindow;
namespace meta_tools {
class PluginManager;
class SaveLoad;
}

/**
 *  メインウインドウクラス.
 *  @author yatagai.
 */
class MainWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    void Initilize();

public:
    void Show();

private:
    Ui::MainWindow *ui;

    // シングルトン.
public:
    static MainWindow* Order()
    {
        return sm_this;
    }
private:
    static MainWindow *sm_this;

    // メインビュー.
private:
    QMainWindow *m_main_view;

    // メニュー最小化スイッチ関係.
public slots:
    void OnMinimizationSwitch();
private:
    void CreateMenuMinimizationSwitch();
private slots:
    void MenuMinimizationSwitchAnimation();
private:
    QTimer m_menu_animate_timer;
    bool m_is_menu_minization;

    // SaveLoad.
private:
    void InitializeSaveLoad();
    void FinalizeSaveLoad();
private:
    meta_tools::SaveLoad *m_save_load;

    // プラグイン関係.
private:
    void InitializePlugins();
    void FinalizePlugins();
private:
    meta_tools::PluginManager *m_plugin_manager;

    // 閉じる.
private:
    virtual void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
