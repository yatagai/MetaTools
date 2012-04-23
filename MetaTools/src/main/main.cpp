/**
 * main.
 * @file main.cpp.
 * @author yatagai.
 */

#include <QtGui/QApplication>
#include <QtGui>
#include "mainwindow.h"

/**
 *  entroy point.
 *  @param in  argc �R�}���h���C�������̐�.
 *  @param in  argv �R�}���h���C������.
 *  @return 0
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // style�ݒ�.
    QApplication::setStyle(QStyleFactory::create("Plastique"));

    MainWindow w;
    w.show();
    
    return a.exec();
}
