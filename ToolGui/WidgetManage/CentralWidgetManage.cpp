#include "CentralWidgetManage.h"

CentralWidgetManage::CentralWidgetManage(CentralWidget* m_centralWidget, QObject* parent)
	:m_centralWidget(m_centralWidget), QObject(parent)
{
	m_pluginDataWidget = m_centralWidget->getPluginDataWidget();
	m_widgetShowWidget = m_centralWidget->getWidgetShowWidget();

	initSignalsSlots();
}

CentralWidgetManage::~CentralWidgetManage()
{}

void CentralWidgetManage::openPlugin(PluginData* pluginData)
{
	clear();

	m_pluginData = pluginData;
	m_widgetShowWidget->showWidget(pluginData->widget);
	m_pluginDataWidget->setPluginData(pluginData);
}

void CentralWidgetManage::updateUI()
{
	m_pluginDataWidget->updateUI();
}

void CentralWidgetManage::clear()
{
	if (m_pluginData)
	{
		m_widgetShowWidget->hideWidget(m_pluginData->widget);
		m_pluginDataWidget->clear();
	}
}

void CentralWidgetManage::initSignalsSlots()
{
	connect(m_pluginDataWidget, &PluginDataWidget::updateDataSignals, this, &CentralWidgetManage::updateDataSignals);
}
