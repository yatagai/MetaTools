/**
 * ���C���E�C���h�E�N���X�̎���.
 * @file mainwindow.cpp.
 * @author yatagai.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * �R���X�g���N�^.
 * @param in parent �e�E�B�W�F�b�g.
 */
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

/**
 * �f�X�g���N�^.
 */
MainWindow::~MainWindow()
{
    delete ui;
}
