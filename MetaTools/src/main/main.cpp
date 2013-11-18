/**
 * main.
 * @file main.cpp.
 * @author yatagai.
 */

#include <QApplication>
#include <QtGui>
#include <QtWidgets>
#include <QTextCodec>
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
    QFile stylesheet(":/metatools_resource/style/metatools_style.qss");
    stylesheet.open(QFile::ReadOnly);
    QString setSheet = QLatin1String(stylesheet.readAll());
    application.setStyleSheet(setSheet);
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    // main window.
    MainWindow main_window;

    // show splash screen.
    SplashScreen *splash_screen = new SplashScreen(&main_window);
    splash_screen->show();

    // show main window.
    main_window.Initilize();
    main_window.show();

    // finish splash screen.
    splash_screen->FinishMainWindowShow();
    splash_screen = nullptr;    // delete on self close.

    return application.exec();
}
