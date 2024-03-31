#pragma once
#include <Qtcore/qglobal.h>

#if defined(MATERIAL_WIDGET)
	#define MATERIAL_WIDGET_API Q_DECL_EXPORT
#else
	#define MATERIAL_WIDGET_API Q_DECL_IMPORT
#endif // defined(MATERIAL_WIDGET)
