﻿#ifndef FONTCREATOR_GLOBAL_H
#define FONTCREATOR_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FONTCREATOR_LIBRARY)
#  define FONTCREATORSHARED_EXPORT Q_DECL_EXPORT
#else
#  define FONTCREATORSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // FONTCREATOR_GLOBAL_H
