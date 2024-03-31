#include "WidgetShowWidget.h"

constexpr int Spacing = 10;	//每10px绘制一个点

WidgetShowWidget::WidgetShowWidget(QWidget* parent)
	: QWidget(parent)
{
	initUI();
	initProperty();
}

WidgetShowWidget::~WidgetShowWidget()
{}

void WidgetShowWidget::showWidget(QWidget* widget)
{
	m_widget = widget;
	widget->setParent(this);
	widget->show();
	widgetCenter();
}

void WidgetShowWidget::hideWidget(QWidget* widget)
{
	m_widget = widget;
	widget->hide();
	widget->setParent(nullptr);
}

void WidgetShowWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setPen(Qt::SolidLine);
	painter.setPen(QColor(QStringLiteral("#a0a0a0")));
	for (int x = 0; x < width(); x += Spacing)
	{
		for (int y = 0; y < height(); y += Spacing)
		{
			painter.drawPoint(x, y);
		}
	}

	QWidget::paintEvent(event);
}

void WidgetShowWidget::resizeEvent(QResizeEvent* event)
{
	if (m_widget)
	{
		widgetCenter();
	}

	QWidget::resizeEvent(event);
}

void WidgetShowWidget::initUI()
{
}

void WidgetShowWidget::initProperty()
{
	this->setProperty("WidgetType", "WidgetShowWidget");
}

void WidgetShowWidget::widgetCenter()
{
	int x = (width() - m_widget->width()) / 2;
	int y = (height() - m_widget->height()) / 2;
	m_widget->move(x, y);
}

