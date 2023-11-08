#include "WidgetShowWidget.h"

constexpr int MinGap = 4;	// 最小线间隔
constexpr int MaxGap = 14;  // 最大线间隔

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
	widget->setParent(this);
	widget->show();
}

void WidgetShowWidget::hideWidget(QWidget* widget)
{
	widget->hide();
	widget->setParent(nullptr);
}


void WidgetShowWidget::initUI()
{
	this->setMinimumSize(600, 200);

	this->m_gap = (MinGap + MaxGap) / 2;
	this->m_startX = this->width() / 2;
	this->m_startY = this->height() / 2;
	this->m_lightPen = QPen(QColor(222, 222, 222));
	this->m_darkPen = QPen(QColor(222, 222, 222));
	this->m_border = QPen(QColor(196, 196, 196));
	this->m_darkPen.setWidth(2);

	this->setBackgroundColor();
}

void WidgetShowWidget::initProperty()
{
	this->setProperty("WidgetType", "WidgetShowWidget");
}

void WidgetShowWidget::setBackgroundColor() {
	QPalette palette;
	palette.setColor(QPalette::Window, QColor(255, 255, 255));
	this->setPalette(palette);
	this->setAutoFillBackground(true);
}

void WidgetShowWidget::drawRowLines(QPainter* painter) {
	int lineCount = 0;
	float biggerY = this->m_startY;
	float smallerY = this->m_startY;

	painter->setPen(this->m_darkPen);

	while (true) {
		painter->drawLine(QPointF(0.0, biggerY), QPointF(this->width(), biggerY));
		painter->drawLine(QPointF(0.0, smallerY), QPointF(this->width(), smallerY));

		biggerY += this->m_gap;
		smallerY -= this->m_gap;
		if (smallerY <= 0 || biggerY >= this->height()) {
			break;
		}

		// 每间隔一定数量的线，就画一条粗一点的横线
		lineCount += 1;
		if (lineCount == 10) {
			painter->setPen(this->m_darkPen);
			lineCount = 0;
		}
		else {
			painter->setPen(this->m_lightPen);
		}
	}

}

void WidgetShowWidget::drawColLines(QPainter* painter) {
	int lineCount = 0;
	float biggerX = this->m_startX;
	float smallerX = this->m_startX;

	painter->setPen(this->m_darkPen);

	while (true) {
		painter->drawLine(QPointF(biggerX, 0.0), QPointF(biggerX, this->height()));
		painter->drawLine(QPointF(smallerX, 0.0), QPointF(smallerX, this->height()));

		biggerX += this->m_gap;
		smallerX -= this->m_gap;
		if (smallerX <= 0 || biggerX >= this->width()) {
			break;
		}

		// 每间隔一定数量的线，就画一条粗一点的竖线
		lineCount += 1;
		if (lineCount == 10) {
			painter->setPen(this->m_darkPen);
			lineCount = 0;
		}
		else {
			painter->setPen(this->m_lightPen);
		}
	}

}

void WidgetShowWidget::drawBorder(QPainter* painter)
{
	int beginX = 0, beginY = 0, endX = this->width(), endY = this->height();

	m_border.setWidth(1);
	painter->setPen(this->m_border);
	painter->drawLine(QPointF(beginX, beginY), QPointF(beginX, endY));
	painter->drawLine(QPointF(beginX, beginY), QPointF(endX, beginY));
	painter->drawLine(QPointF(beginX, endY), QPointF(endX, endY));
	painter->drawLine(QPointF(endX, beginY), QPointF(endX, endY));
}

void WidgetShowWidget::paintEvent(QPaintEvent* event) {
	QWidget::paintEvent(event);
	QPainter painter(this);
	this->drawRowLines(&painter);
	this->drawColLines(&painter);
	this->drawBorder(&painter);
}

void WidgetShowWidget::wheelEvent(QWheelEvent* event) {
	QWidget::wheelEvent(event);
	if (event->angleDelta().y() > 0) {
		this->m_gap += 0.1;
	}
	else if (event->angleDelta().y() < 0) {
		this->m_gap -= 0.1;
	}

	if (this->m_gap >= MaxGap) {
		this->m_gap = MinGap;
	}
	else if (this->m_gap <= MinGap) {
		this->m_gap = MaxGap;
	}

	this->update();
}

void WidgetShowWidget::resizeEvent(QResizeEvent* event) {
	QWidget::resizeEvent(event);
	this->m_startX = this->width() / 2;
	this->m_startY = this->height() / 2;
	this->update();
}