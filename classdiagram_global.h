#ifndef CLASSDIAGRAM_GLOBAL_H
#define CLASSDIAGRAM_GLOBAL_H

#include <QtGlobal>

#if defined(CLASSDIAGRAM_LIBRARY)
#  define CLASSDIAGRAMSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CLASSDIAGRAMSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CLASSDIAGRAM_GLOBAL_H

