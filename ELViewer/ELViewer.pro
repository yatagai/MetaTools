#-------------------------------------------------
#
# Project created by QtCreator 2013-05-09T01:36:23
#
#-------------------------------------------------

QT       += widgets

TARGET = ELViewer
TEMPLATE = lib

DEFINES += ELVIEWER_LIBRARY

SOURCES += elviewer.cpp

HEADERS += elviewer.h\
        elviewer_global.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
