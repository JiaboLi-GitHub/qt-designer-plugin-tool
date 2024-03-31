#pragma once
#include <Qtcore/qglobal.h>

#if defined(SHARED_LIBRARY_EXPORT)
#define SHARED_LIBRARY_API Q_DECL_EXPORT
#else
#define SHARED_LIBRARY_API Q_DECL_IMPORT
#endif // defined(SHARED_LIBRARY_EXPORT)
