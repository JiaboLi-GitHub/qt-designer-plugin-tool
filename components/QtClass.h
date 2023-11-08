#pragma once

#include <QtWidgets/QWidget>
#include "SharedExport.h"
class MATERIAL_WIDGET_API QtClass : public QWidget
{
	Q_OBJECT

public:
	QtClass(QWidget* parent = nullptr);
	~QtClass();
};
