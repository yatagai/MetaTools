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

    // メニュー最小化スイッチ関係.
public slots:
    void OnMinimizationSwitch();
private:
    void CreateMenuMinimizationSwitch();
private slots:
    void MenuMinimizationSwitchAnimation();
private:
    QTimer m_menu_animate_timer;
    float m_is_menu_minization;
};

#endif // MAINWINDOW_H
