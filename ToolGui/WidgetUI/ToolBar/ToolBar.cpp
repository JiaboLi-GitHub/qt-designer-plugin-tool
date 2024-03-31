#include "ToolBar.h"

#include <qfiledialog.h>
#include <qmainwindow.h>
#include <QVBoxLayout>
#include <qpushbutton.h>
#include"components/qtmaterialdialog.h"
#include "components/qtmaterialflatbutton.h"
#include "WidgetUI/CentralWidget/CentralWidget.h"
#include "WidgetUI/ToolBar/OpenDialog.h"
#include "ToolGui/WidgetUI/ToolBar/SetupDialog.h"
#include "ToolGui/WidgetUI/ToolBar/MatchDialog.h"


ToolBar::ToolBar(QWidget* parent)
	: QToolBar(parent)
{
	initUI();
	initSignalsSlots();
}

ToolBar::~ToolBar()
{}

void ToolBar::setIsOpenPlugin(bool isOpenPlugin)
{
	m_isOpenPlugin = isOpenPlugin;
}

void ToolBar::initUI()
{
	this->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

	m_btnList = { &m_newBtn,&m_openBtn ,&m_saveBtn ,&m_installBtn ,&m_closeBtn,&m_setupBtn ,&m_matchBtn };
	for (auto& btn : m_btnList)
	{
		*btn = new QToolButton(this);
		(*btn)->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

		this->addWidget(*btn);
	}
	m_newBtn->setText("新建");
	m_openBtn->setText("打开");
	m_saveBtn->setText("保存");
	m_installBtn->setText("安装");
	m_closeBtn->setText("关闭");
	m_setupBtn->setText("设置");
	m_matchBtn->setText("匹配");
	m_newBtn->setProperty("ToolButton", "newBtn");
	m_openBtn->setProperty("ToolButton", "openBtn");
	m_saveBtn->setProperty("ToolButton", "saveBtn");
	m_installBtn->setProperty("ToolButton", "installBtn");
	m_closeBtn->setProperty("ToolButton", "deleteBtn");
	m_setupBtn->setProperty("ToolButton", "setupBtn");
	m_matchBtn->setProperty("ToolButton", "matchBtn");

	setStyleSheet("background-color: rgb(255, 255, 255);");
}

void ToolBar::initSignalsSlots()
{
	connect(m_newBtn, &QAbstractButton::clicked, this, &ToolBar::on_newBtn_clicked);
	connect(m_openBtn, &QAbstractButton::clicked, this, &ToolBar::on_openBtn_clicked);
	connect(m_closeBtn, &QAbstractButton::clicked, this, &ToolBar::on_closeBtn_clicked);
	connect(m_saveBtn, &QAbstractButton::clicked, this, &ToolBar::on_saveBtn_clicked);
	connect(m_installBtn, &QAbstractButton::clicked, this, &ToolBar::on_installBtn_clicked);
	connect(m_setupBtn, &QAbstractButton::clicked, this, &ToolBar::on_setupBtn_clicked);
	connect(m_matchBtn, &QAbstractButton::clicked, this, &ToolBar::on_matchBtn_clicked);
}


void ToolBar::on_newBtn_clicked(bool checked)
{
	QString fileName = QFileDialog::getOpenFileName(this, "导入控件动态库以新建插件库", "", "*.dll");
	if (!fileName.isEmpty())
		emit newPluginSignals(fileName);
}

void ToolBar::on_openBtn_clicked(bool checked)
{
	OpenDialog* openDialog = new OpenDialog(this);
	openDialog->open();
	connect(openDialog, &QDialog::finished, this, &ToolBar::openDialogFinished);
}

void ToolBar::on_closeBtn_clicked(bool checked)
{
	emit closePluginSignals();
}

void ToolBar::on_saveBtn_clicked(bool checked)
{
	emit savePluginSignals();
}

void ToolBar::on_installBtn_clicked(bool checked)
{
	emit installPluginSignals();
}

void ToolBar::on_setupBtn_clicked(bool checked)
{
	SetupDialog* setupDialog = new SetupDialog(this);
	setupDialog->open();
	connect(setupDialog, &QDialog::finished, this, &ToolBar::setupDialogFinished);
}

void ToolBar::on_matchBtn_clicked(bool checked)
{
	MatchDialog* matchDialog = new MatchDialog(this);
	matchDialog->open();
	connect(matchDialog, &QDialog::finished, this, &ToolBar::matchDialogFinished);
}

void ToolBar::openDialogFinished(int result)
{
	OpenDialog* openDialog = qobject_cast<OpenDialog*>(QObject::sender());
	if (result == QDialog::Accepted)
	{
		QString path = openDialog->getPluginPath();
		emit openPluginSignals(path);
	}
	openDialog->deleteLater();
}

void ToolBar::setupDialogFinished(int result)
{
	SetupDialog* setupDialog = qobject_cast<SetupDialog*>(QObject::sender());
	if (result == QDialog::Accepted)
	{
		QString qtPath = setupDialog->getQtPath();
		emit setupSignals(qtPath);
	}
	setupDialog->deleteLater();
}

void ToolBar::matchDialogFinished(int result)
{
	MatchDialog* matchDialog = qobject_cast<MatchDialog*>(QObject::sender());
	if (result == QDialog::Accepted)
	{
		QString path = matchDialog->getPath();
		emit matchSignals(path);
	}
	matchDialog->deleteLater();
}
