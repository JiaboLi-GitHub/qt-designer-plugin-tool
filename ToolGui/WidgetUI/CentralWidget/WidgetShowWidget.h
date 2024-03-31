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
	void paintEvent(QPaintEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;

private:
	void initUI();
	void initProperty();
	void widgetCenter();

private:
	QWidget* m_widget = nullptr;
};
