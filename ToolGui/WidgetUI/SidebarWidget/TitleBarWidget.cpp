#include "TitleBarWidget.h"
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QLabel>

TitleBarWidget::TitleBarWidget(QWidget* parent) : QWidget(parent)
{
	initUI();
}
TitleBarWidget::~TitleBarWidget()
{
}
void TitleBarWidget::mousePressEvent(QMouseEvent* e)
{
	QWidget::mousePressEvent(e);
}
void TitleBarWidget::mouseReleaseEvent(QMouseEvent* e)
{
	QWidget::mouseReleaseEvent(e);
}
void TitleBarWidget::mouseMoveEvent(QMouseEvent* e)
{
	QWidget::mouseMoveEvent(e);
}

void TitleBarWidget::initUI()
{
	//this->setFixedHeight(20);
	QVBoxLayout* vBoxLayout = new QVBoxLayout(this);
	auto label = new QLabel("插件管理器", this);
	label->setFixedHeight(15);
	vBoxLayout->addWidget(label);
	this->setLayout(vBoxLayout);
	this->setContentsMargins(0, 0, 0, 0);
	vBoxLayout->setContentsMargins(0, 0, 0, 0);
	setStyleSheet("background-color:  #E6E6E6;");
}
