#ifndef METATOOLSPLUGIN_GLOBAL_H
#define METATOOLSPLUGIN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(METATOOLSPLUGIN_LIBRARY)
#  define METATOOLSPLUGINSHARED_EXPORT Q_DECL_EXPORT
#else
#  define METATOOLSPLUGINSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // METATOOLSPLUGIN_GLOBAL_H