#-------------------------------------------------
#
# Project created by QtCreator 2012-04-22T04:48:51
#
#-------------------------------------------------

QT       += core gui

unix: QMAKE_CXXFLAGS += -std=c++0x

TARGET = MetaTools
TEMPLATE = app


SOURCES += src/main/main.cpp \
    src/main/mainwindow.cpp \
    src/metatools_tooltip/metatools_tooltip.cpp \
    src/plugin/plugin_manager/plugin_manager.cpp \
    src/plugin/plugin_connect_func.cpp \
    src/plugin/build_in_plugin/home_menu_plugin.cpp \
    src/plugin/build_in_plugin/log_plugin.cpp

HEADERS  += src/main/mainwindow.h \
    src/metatools_tooltip/metatools_tooltip.h \
    src/plugin/plugin_manager/plugin_manager.h \
    src/plugin/build_in_plugin/home_menu_plugin.h \
    src/plugin/build_in_plugin/log_plugin.h

FORMS    += src/metatools_tooltip/metatools_tooltip.ui \
    src/main/mainwindow.ui \
    src/plugin/build_in_plugin/log_window.ui \
    src/plugin/build_in_plugin/home_menu.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../MetaToolsPlugin-MSVC/release/ -lMetaToolsPlugin
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../MetaToolsPlugin-MSVC/debug/ -lMetaToolsPlugin
else:symbian: LIBS += -lMetaToolsPlugin
else:unix: LIBS += -L$$PWD/../MetaToolsPlugin-GCC-Release/ -lMetaToolsPlugin

INCLUDEPATH += $$PWD/../MetaToolsPlugin
DEPENDPATH += $$PWD/../MetaToolsPlugin

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../MetaToolsPlugin-MSVC/release/MetaToolsPlugin.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../MetaToolsPlugin-MSVC/debug/MetaToolsPlugin.lib
else:unix:!symbian: PRE_TARGETDEPS += $$PWD/../MetaToolsPlugin-GCC-Release/libMetaToolsPlugin.a

RESOURCES += \
    MetaToolsResource.qrc
