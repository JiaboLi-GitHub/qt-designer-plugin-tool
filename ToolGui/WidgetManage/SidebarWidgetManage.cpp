#include "SidebarWidgetManage.h"

#include <QApplication>

SidebarWidgetManage::SidebarWidgetManage(SidebarWidget* widget, QObject* parent)
	: QObject(parent), m_sidebarWidget(widget)
{
	m_treeModel = new QStandardItemModel(this);
	m_listModel = new QStandardItemModel(this);
	m_sidebarWidget->initView(m_treeModel, m_listModel);
	initSignalsSlots();
}

SidebarWidgetManage::~SidebarWidgetManage()
{}

void SidebarWidgetManage::initModel(const QMap<QString, PluginData*>& pluginDataMap)
{
	for (auto iter = pluginDataMap.begin(); iter != pluginDataMap.end(); ++iter)
	{
		auto pluginData = iter.value();
		if (pluginData->isPack)
		{
			appendTreeItem(pluginData);
		}
		else
		{
			appendListItem(pluginData);
		}
	}
}

void SidebarWidgetManage::updateData(const PluginData* pluginData)
{
	if (pluginData->isPack)
	{
		if (containsTreeItem(pluginData))
		{
			updateTreeItem(pluginData);
		}
		else
		{
			removeListItem(pluginData);
			appendTreeItem(pluginData);
		}
	}
	else
	{
		if (containsTreeItem(pluginData))
		{
			removeTreeItem(pluginData);
			appendListItem(pluginData);
		}
		else
		{
			updateListItem(pluginData);
		}
	}
}

void SidebarWidgetManage::clear()
{
	m_listItemList.clear();
	m_listModel->clear();

	m_treeItemMap.clear();
	m_rootItemMap.clear();
	m_treeModel->clear();
}

void SidebarWidgetManage::initSignalsSlots()
{
	connect(m_sidebarWidget, &SidebarWidget::doubleClickedSignals, this, &SidebarWidgetManage::doubleClicked);
}

void SidebarWidgetManage::appendTreeItem(const PluginData* pluginData)
{
	if (!m_treeItemMap.contains(pluginData->group))
	{
		auto rootItem = new QStandardItem(pluginData->group);
		m_treeModel->appendRow(rootItem);
		m_rootItemMap.insert(pluginData->group, rootItem);
		m_treeItemMap.insert(pluginData->group, QList<QStandardItem*>());
	}
	QStandardItem* item = new QStandardItem(QIcon(pluginData->icon), pluginData->className);
	if (pluginData->icon.isEmpty())
	{
		item->setIcon(QApplication::style()->standardIcon((enum QStyle::StandardPixmap)0));
	}

	m_rootItemMap[pluginData->group]->appendRow(item);
	m_treeItemMap[pluginData->group].append(item);
}

void SidebarWidgetManage::updateTreeItem(const PluginData* pluginData)
{
	if (!m_treeItemMap.contains(pluginData->group))
		return;

	auto itemList = m_treeItemMap[pluginData->group];
	for (auto& item : itemList)
	{
		if (item->text() == pluginData->className)
		{
			item->setIcon(QIcon(pluginData->icon));
			break;
		}
	}
}

void SidebarWidgetManage::removeTreeItem(const PluginData* pluginData)
{
	if (!m_treeItemMap.contains(pluginData->group))
		return;

	QList<QStandardItem*>& itemList = m_treeItemMap[pluginData->group];
	for (int i = 0; i < itemList.size(); i++)
	{
		if (itemList.at(i)->text() == pluginData->className)
		{
			m_rootItemMap[pluginData->group]->removeRow(itemList.at(i)->row());
			itemList.removeAt(i);
			break;
		}
	}
	if (!itemList.size())
	{
		m_treeModel->removeRow(m_rootItemMap[pluginData->group]->row());
		m_rootItemMap.remove(pluginData->group);
		m_treeItemMap.remove(pluginData->group);
	}
}

bool SidebarWidgetManage::containsTreeItem(const PluginData* pluginData)
{
	if (!m_treeItemMap.contains(pluginData->group))
		return false;

	for (auto& item : m_treeItemMap[pluginData->group])
	{
		if (item->text() == pluginData->className)
			return true;
	}
	return false;
}

void SidebarWidgetManage::appendListItem(const PluginData* pluginData)
{
	QStandardItem* item = new QStandardItem(QIcon(pluginData->icon), pluginData->className);
	if (pluginData->icon.isEmpty())
	{
		item->setIcon(QApplication::style()->standardIcon((enum QStyle::StandardPixmap)0));
	}
	m_listModel->appendRow(item);
	m_listItemList.append(item);
}

void SidebarWidgetManage::updateListItem(const PluginData* pluginData)
{
	for (auto& item : m_listItemList)
	{
		if (item->text() == pluginData->className)
		{
			item->setIcon(QIcon(pluginData->icon));
			break;
		}
	}
}

void SidebarWidgetManage::removeListItem(const PluginData* pluginData)
{
	for (int i = 0; i < m_listItemList.size(); i++)
	{
		auto item = m_listItemList.at(i);
		if (item->text() == pluginData->className)
		{
			m_listModel->removeRow(item->row());
			m_listItemList.removeAt(i);
		}
	}
}


void SidebarWidgetManage::doubleClicked(const QModelIndex& index)
{
	auto model = (QStandardItemModel*)(index.model());
	if (model)
	{
		auto item = model->itemFromIndex(index);
		if (item)
		{
			QString className = item->text();
			for (auto& rootItem : m_rootItemMap.values())
			{
				if (className == rootItem->text())
					return;
			}

			emit doubleClickedSignals(className);
		}
	}
}
