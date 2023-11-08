#pragma once
#include <QWidget>
class TitleBarWidget : public QWidget
{
	Q_OBJECT
public:
	explicit TitleBarWidget(QWidget* parent = nullptr);
	~TitleBarWidget();

protected:
	virtual void mousePressEvent(QMouseEvent*)override;
	virtual void mouseReleaseEvent(QMouseEvent*)override;
	virtual void mouseMoveEvent(QMouseEvent*)override;

private:
	void initUI();


};