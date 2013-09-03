#-------------------------------------------------
#
# Project created by QtCreator 2012-06-11T05:21:52
#
#-------------------------------------------------

QT       += widgets
TARGET = FontCreator
TEMPLATE = lib

DEFINES += FONTCREATOR_LIBRARY
DEFINES += FT2_BUILD_LIBRARY
DEFINES += _CRT_SECURE_NO_WARNINGS

INCLUDEPATH += lib/freetype/include

SOURCES += \
    lib/freetype/src/base/ftbbox.c \
    lib/freetype/src/base/ftgxval.c \
    lib/freetype/src/base/ftlcdfil.c \
    lib/freetype/src/base/ftmm.c \
    lib/freetype/src/base/ftotval.c \
    lib/freetype/src/base/ftpatent.c \
    lib/freetype/src/base/ftpfr.c \
    lib/freetype/src/base/ftsynth.c \
    lib/freetype/src/base/fttype1.c \
    lib/freetype/src/base/ftwinfnt.c \
    lib/freetype/src/base/ftxf86.c \
    lib/freetype/src/pcf/pcf.c \
    lib/freetype/src/pfr/pfr.c \
    lib/freetype/src/psaux/psaux.c \
    lib/freetype/src/pshinter/pshinter.c \
    lib/freetype/src/psnames/psmodule.c \
    lib/freetype/src/raster/raster.c \
    lib/freetype/src/sfnt/sfnt.c \
    lib/freetype/src/truetype/truetype.c \
    lib/freetype/src/type1/type1.c \
    lib/freetype/src/cid/type1cid.c \
    lib/freetype/src/type42/type42.c \
    lib/freetype/src/winfonts/winfnt.c \
    lib/freetype/src/autofit/autofit.c \
    lib/freetype/src/bdf/bdf.c \
    lib/freetype/src/cff/cff.c \
    lib/freetype/src/base/ftbase.c \
    lib/freetype/src/base/ftbitmap.c \
    lib/freetype/src/cache/ftcache.c \
    lib/freetype/src/base/ftfstype.c \
    lib/freetype/src/base/ftgasp.c \
    lib/freetype/src/base/ftglyph.c \
    lib/freetype/src/gzip/ftgzip.c \
    lib/freetype/src/base/ftinit.c \
    lib/freetype/src/lzw/ftlzw.c \
    lib/freetype/src/base/ftstroke.c \
    lib/freetype/src/base/ftsystem.c \
    lib/freetype/src/smooth/smooth.c \
    src/fontcreator_plugin.cpp \
    src/fontcreator_widget.cpp \
    src/fontloader.cpp

HEADERS +=\
    lib/freetype/include/ft2build.h \
    lib/freetype/include/freetype/config/ftconfig.h \
    lib/freetype/include/freetype/config/ftheader.h \
    lib/freetype/include/freetype/config/ftmodule.h \
    lib/freetype/include/freetype/config/ftoption.h \
    lib/freetype/include/freetype/config/ftstdlib.h \
    src/FontCreator_global.h \
    src/fontcreator_plugin.h \
    src/fontcreator_widget.h \
    src/fontloader.h

FORMS += \
    src/main_form/main_form.ui

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

#deploy setting.
win32 {
    CONFIG(debug, debug|release) {
        DESTDIR = ../bin/win32d/plugins
    } else {
        DESTDIR = ../bin/win32/plugins
    }
}
unix {
    CONFIG(debug, debug|release) {
        DESTDIR = ../bin/linuxd/plugins
    } else {
        DESTDIR = ../bin/linux/plugins
    }
}
