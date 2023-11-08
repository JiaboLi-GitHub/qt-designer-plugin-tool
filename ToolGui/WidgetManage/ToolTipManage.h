#pragma once

#include <QObject>
#include "components/qtmaterialsnackbar.h"

enum class ToolTipType
{
	Correct,
	Error
};



class ToolTipManage : public QObject
{
	Q_OBJECT

public:
	ToolTipManage(QObject* parent);
	~ToolTipManage();

	static void initInstance(QWidget* parent);
	static void showToolTip(const QString& text);

private:
	static QtMaterialSnackbar* m_toolTip;

};
