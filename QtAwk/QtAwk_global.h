#ifndef QTAWK_GLOBAL_H
#define QTAWK_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QTAWK_LIBRARY)
#  define QTAWK_EXPORT Q_DECL_EXPORT
#else
#  define QTAWK_EXPORT Q_DECL_IMPORT
#endif

#endif // QTAWK_GLOBAL_H
