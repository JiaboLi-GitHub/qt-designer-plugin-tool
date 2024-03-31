#include "SidebarWidget.h"
#include <qboxlayout.h>
#include <qheaderview.h>

SidebarWidget::SidebarWidget(QWidget* parent)
	: QWidget(parent)
{
	initUI();
	initSignalsSlots();
}

SidebarWidget::~SidebarWidget()
{}

void SidebarWidget::initUI()
{
	m_tabWidget = new QTabWidget(this);

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(m_tabWidget);
	this->setLayout(layout);
	layout->setContentsMargins(0, 0, 0, 0);

	m_treeView = new QTreeView(m_tabWidget);
	m_listView = new QListView(m_tabWidget);
	m_tabWidget->addTab(m_treeView, "已封装");
	m_tabWidget->addTab(m_listView, "未封装");
	m_treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

	m_treeView->header()->hide();

	this->setStyleSheet(R"(
		QWidget { background-color: white; }
	)");
	m_tabWidget->setStyleSheet(R"(
		QTabWidget { background-color: white; }
		QTabWidget::pane { border: none; }
	)");
}

void SidebarWidget::initSignalsSlots()
{
	connect(m_treeView, &QAbstractItemView::clicked, this, &SidebarWidget::doubleClickedSignals);
	connect(m_listView, &QAbstractItemView::clicked, this, &SidebarWidget::doubleClickedSignals);
}

void SidebarWidget::initView(QStandardItemModel* treeModel, QStandardItemModel* listModel)
{
	m_treeView->setModel(treeModel);
	m_listView->setModel(listModel);
}
