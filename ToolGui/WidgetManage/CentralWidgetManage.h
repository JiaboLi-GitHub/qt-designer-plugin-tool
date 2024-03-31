#pragma once

#include <QObject>
#include "WidgetUI/CentralWidget/CentralWidget.h"
#include "SharedLibrary/Data/PluginLibraryData.h"

class CentralWidgetManage : public QObject
{
	Q_OBJECT

public:
	CentralWidgetManage(CentralWidget* m_centralWidget, QObject* parent);
	~CentralWidgetManage();

	void openPlugin(PluginData* pluginData);
	void updateUI();
	void clear();

private:
	void initSignalsSlots();


signals:
	void updateDataSignals(const PluginData* m_pluginData);

private:
	CentralWidget* m_centralWidget = nullptr;
	PluginDataWidget* m_pluginDataWidget = nullptr;
	WidgetShowWidget* m_widgetShowWidget = nullptr;
	PluginData* m_pluginData = nullptr;
};
