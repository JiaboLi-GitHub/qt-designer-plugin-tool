#include "CentralWidget.h"

#include <QVBoxLayout>

CentralWidget::CentralWidget(QWidget* parent)
	: QSplitter(parent)
{
	initUI();
}

CentralWidget::~CentralWidget()
{

}

PluginDataWidget* CentralWidget::getPluginDataWidget()
{
	return m_pluginDataWidget;
}

WidgetShowWidget* CentralWidget::getWidgetShowWidget()
{
	return m_widgetShowWidget;
}

void CentralWidget::initUI()
{
	this->setOrientation(Qt::Vertical);

	m_widgetShowWidget = new WidgetShowWidget(this);
	m_pluginDataWidget = new PluginDataWidget(this);

	this->addWidget(m_widgetShowWidget);
	this->addWidget(m_pluginDataWidget);
}
