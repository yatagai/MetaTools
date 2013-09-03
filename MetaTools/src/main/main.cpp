/**
 * main.
 * @file main.cpp.
 * @author yatagai.
 */

#include <QApplication>
#include <QtGui>
#include <QtWidgets>
#include "mainwindow.h"
#include "../splash_screen/splash_screen.h"
/**
 *  @brief      entroy point.
 *  @param  in  argc コマンドライン引数の数.
 *  @param  in  argv コマンドライン引数.
 *  @return     0
 */
int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    // style設定.
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    // show main window.
    SplashScreen *splash_screen = new SplashScreen();
    splash_screen->show();
    splash_screen->setWindowOpacity(0.0f);

    QApplication::flush();

    // show main window.
    MainWindow main_window;
    main_window.show();

    // finish splash screen.
    splash_screen->FinishMainWindowShow();
    splash_screen = nullptr;    // delete on self close.

    return application.exec();
}
