#pragma once

#include <QWidget>
#include <QPen>
#include <QPainter>
#include <QPaintEvent>

class WidgetShowWidget : public QWidget
{
	Q_OBJECT

public:
	WidgetShowWidget(QWidget* parent = nullptr);
	~WidgetShowWidget();

	void showWidget(QWidget* widget);
	void hideWidget(QWidget* widget);

protected:
	void paintEvent(QPaintEvent* event);
	void wheelEvent(QWheelEvent* event);
	void resizeEvent(QResizeEvent* event);

private:
	void initUI();
	void initProperty();
	void setBackgroundColor();              // 设置窗口背景颜色
	void drawRowLines(QPainter* painter);   // 绘制横线
	void drawColLines(QPainter* painter);   // 绘制竖线
	void drawBorder(QPainter* painter);

private:
	float m_gap;                               // 当前线间隔
	float m_startX;                            // 竖线初始x坐标（从窗口中间开始）
	float m_startY;                            // 横线初始y坐标（从窗口中间开始）
	QPen m_lightPen;                           // 细一点的画笔
	QPen m_darkPen;                            // 粗一点的画笔
	QPen m_border;
};
