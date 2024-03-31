#pragma once

#include <QWidget>
#include <qtabwidget.h>
#include <qlistview.h>
#include <qtreeview.h>
#include <qstandarditemmodel.h>

class SidebarWidget : public QWidget
{
	Q_OBJECT

public:
	SidebarWidget(QWidget* parent = nullptr);
	~SidebarWidget();

	void initView(QStandardItemModel* treeModel, QStandardItemModel* listModel);

private:
	void initUI();
	void initSignalsSlots();

signals:
	void doubleClickedSignals(const QModelIndex& index);

private:
	QTabWidget* m_tabWidget = nullptr;
	QListView* m_listView = nullptr;
	QTreeView* m_treeView = nullptr;
};
