#-------------------------------------------------
#
# Project created by QtCreator 2012-04-22T04:48:51
#
#-------------------------------------------------

QT       += core gui widgets

unix: QMAKE_CXXFLAGS += -std=c++0x

TARGET = MetaTools
TEMPLATE = app


SOURCES += src/main/main.cpp \
    src/main/mainwindow.cpp \
    src/metatools_tooltip/metatools_tooltip.cpp \
    src/tool_widget_form/tool_widget_form.cpp \
    src/plugin/plugin_connect_func.cpp \
    src/plugin/plugin_manager/plugin_manager.cpp \
    src/plugin/build_in_plugin/log_plugin/log_plugin.cpp \
    src/plugin/build_in_plugin/home_menu_plugin/home_menu_plugin.cpp \
    src/plugin/build_in_plugin/home_menu_plugin/home_menu_plugin_widget.cpp \
    src/plugin/build_in_plugin/home_menu_plugin/plugin_manager_widget.cpp \
    src/plugin/build_in_plugin/home_menu_plugin/plugin_widget.cpp \
    src/splash_screen/splash_screen.cpp

HEADERS  += src/main/mainwindow.h \
    src/metatools_tooltip/metatools_tooltip.h \
    src/tool_widget_form/tool_widget_form.h \
    src/plugin/plugin.h \
    src/plugin/plugin_manager/plugin_manager.h \
    src/plugin/build_in_plugin/log_plugin/log_plugin.h \
    src/plugin/build_in_plugin/home_menu_plugin/home_menu_plugin.h \
    src/plugin/build_in_plugin/home_menu_plugin/home_menu_plugin_widget.h \
    src/plugin/build_in_plugin/home_menu_plugin/plugin_manager_widget.h \
    src/plugin/build_in_plugin/home_menu_plugin/plugin_widget.h \
    src/splash_screen/splash_screen.h

FORMS    += src/main/mainwindow.ui \
    src/metatools_tooltip/metatools_tooltip.ui \
    src/plugin/build_in_plugin/log_plugin/log_window.ui \
    src/plugin/build_in_plugin/home_menu_plugin/home_menu.ui \
    src/plugin/build_in_plugin/home_menu_plugin/plugin_manager.ui \
    src/plugin/build_in_plugin/home_menu_plugin/plugin_widget.ui \
    src/splash_screen/splash_screen.ui \
    src/tool_widget_form/tool_widget_form.ui

RESOURCES += \
    MetaToolsResource.qrc

#deploy setting.
win32 {
    RC_FILE += windows.rc
    QMAKE_LFLAGS += /MANIFEST:NO
    CONFIG -= embed_manifest_exe
    CONFIG(debug, debug|release) {
        DESTDIR = ../bin/win32d
    } else {
        DESTDIR = ../bin/win32
    }
}
unix {
    CONFIG(debug, debug|release) {
        DESTDIR = ../bin/linuxd
    } else {
        DESTDIR = ../bin/linux
    }
}
