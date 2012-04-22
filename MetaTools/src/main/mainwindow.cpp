#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * コンストラクタ.
 * param in parent 親ウィジェット.
 */
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

/**
 * デストラクタ.
 */
MainWindow::~MainWindow()
{
    delete ui;
}
