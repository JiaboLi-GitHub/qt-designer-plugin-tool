#pragma once

#include <QObject>
#include <qlist.h>
#include <qstandarditemmodel.h>
#include "SharedLibrary/Data/PluginLibraryData.h"
#include "WidgetUI/SidebarWidget/SidebarWidget.h"

class SidebarWidgetManage : public QObject
{
	Q_OBJECT

public:
	SidebarWidgetManage(SidebarWidget* widget, QObject* parent);
	~SidebarWidgetManage();

	void initModel(const QMap<QString, PluginData*>& pluginDataMap);
	void updateData(const PluginData* pluginData);
	void clear();

private:
	void initSignalsSlots();
	void appendTreeItem(const PluginData* pluginData);
	void updateTreeItem(const PluginData* pluginData);
	void removeTreeItem(const PluginData* pluginData);
	bool containsTreeItem(const PluginData* pluginData);

	void appendListItem(const PluginData* pluginData);
	void updateListItem(const PluginData* pluginData);
	void removeListItem(const PluginData* pluginData);


signals:
	void doubleClickedSignals(const QString& className);

public slots:
	void doubleClicked(const QModelIndex& index);


private:
	SidebarWidget* m_sidebarWidget;

	//TODO这块区域改成智能指针
	QStandardItemModel* m_treeModel;
	QMap<QString, QList<QStandardItem*>> m_treeItemMap;//分组:模型数据列表
	QMap<QString, QStandardItem*> m_rootItemMap;

	QStandardItemModel* m_listModel;
	QList<QStandardItem*> m_listItemList;
};
