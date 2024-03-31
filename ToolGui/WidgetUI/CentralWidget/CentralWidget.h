#pragma once

#include <QSplitter>
#include "PluginDataWidget.h"
#include "WidgetShowWidget.h"


class CentralWidget : public QSplitter
{
	Q_OBJECT

public:
	CentralWidget(QWidget* parent);
	~CentralWidget();

	PluginDataWidget* getPluginDataWidget();
	WidgetShowWidget* getWidgetShowWidget();

private:
	void initUI();

private:
	PluginDataWidget* m_pluginDataWidget = nullptr;
	WidgetShowWidget* m_widgetShowWidget = nullptr;
};
