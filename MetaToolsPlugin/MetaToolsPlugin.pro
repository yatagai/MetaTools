#-------------------------------------------------
#
# Project created by QtCreator 2012-04-23T02:14:23
#
#-------------------------------------------------

TARGET = MetaToolsPlugin
TEMPLATE = lib

DEFINES += METATOOLSPLUGIN_LIBRARY

SOURCES += \
    plugin.cpp

HEADERS +=\
        MetaToolsPlugin_global.h \
    plugin.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE48BED92
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = MetaToolsPlugin.dll
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
