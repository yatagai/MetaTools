/**
 * ���C���E�C���h�E�N���X�̒�`.
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
 *  ���C���E�C���h�E�N���X.
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
