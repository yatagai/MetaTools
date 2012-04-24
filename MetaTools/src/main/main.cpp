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
 *  @param in  argc コマンドライン引数の数.
 *  @param in  argv コマンドライン引数.
 *  @return 0
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // style設定.
    QApplication::setStyle(QStyleFactory::create("Plastique"));

    MainWindow w;
    w.show();
    
    return a.exec();
}
