#-------------------------------------------------
#
# Project created by QtCreator 2012-06-11T05:21:52
#
#-------------------------------------------------

TARGET = FontCreator
TEMPLATE = lib

DEFINES += FONTCREATOR_LIBRARY

SOURCES += \
    src/fontcreator_plugin.cpp

HEADERS +=\
    src/FontCreator_global.h \
    src/fontcreator_plugin.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE0E04333
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = FontCreator.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

RESOURCES += \
    FontCreator.qrc
