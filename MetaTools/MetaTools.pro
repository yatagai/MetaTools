#-------------------------------------------------
#
# Project created by QtCreator 2012-04-22T04:48:51
#
#-------------------------------------------------

QT       += core gui

TARGET = MetaTools
TEMPLATE = app


SOURCES += src/main/main.cpp \
    src/main/mainwindow.cpp \
    src/metatools_tooltip/metatools_tooltip.cpp \
    src/plugin/plugin_manager/plugin_manager.cpp \
    src/plugin/plugin_connect_func.cpp

HEADERS  += src/main/mainwindow.h \
    src/metatools_tooltip/metatools_tooltip.h \
    src/plugin/plugin_manager/plugin_manager.h

FORMS    += src/metatools_tooltip/metatools_tooltip.ui \
    src/main/mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../MetaToolsPlugin-build-desktop-Qt_4_8_1_for_Desktop_-_MSVC2010__Qt_SDK/release/ -lMetaToolsPlugin
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../MetaToolsPlugin-build-desktop-Qt_4_8_1_for_Desktop_-_MSVC2010__Qt_SDK/debug/ -lMetaToolsPlugin
else:symbian: LIBS += -lMetaToolsPlugin
else:unix: LIBS += -L$$PWD/../MetaToolsPlugin-GCC-Release/ -lMetaToolsPlugin

INCLUDEPATH += $$PWD/../MetaToolsPlugin
DEPENDPATH += $$PWD/../MetaToolsPlugin

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../MetaToolsPlugin-build-desktop-Qt_4_8_1_for_Desktop_-_MSVC2010__Qt_SDK/release/MetaToolsPlugin.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../MetaToolsPlugin-build-desktop-Qt_4_8_1_for_Desktop_-_MSVC2010__Qt_SDK/debug/MetaToolsPlugin.lib
else:unix:!symbian: PRE_TARGETDEPS += $$PWD/../MetaToolsPlugin-GCC-Release/libMetaToolsPlugin.a
