/**
 * メインウインドウクラスの定義.
 * @file mainwindow.h.
 * @author yatagai.
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

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
};

#endif // MAINWINDOW_H
