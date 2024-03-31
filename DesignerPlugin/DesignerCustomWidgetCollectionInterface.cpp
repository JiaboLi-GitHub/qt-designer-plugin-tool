#include "DesignerCustomWidgetCollectionInterface.h"

#include "SharedLibrary/Utility/FileUtility.h"
#include "SharedLibrary/Utility/JsonUtility.h"
#include "SharedLibrary/Utility/LibraryUtility.h"
#include "DesignerCustomWidgetInterface.h"

constexpr const char PluginRootPath[] = "../plugins/designer/DesignerData";

DesignerCustomWidgetCollectionInterface::DesignerCustomWidgetCollectionInterface(QObject* parent) : QObject(parent)
{
	initData();
}

DesignerCustomWidgetCollectionInterface::~DesignerCustomWidgetCollectionInterface()
{
}

QList<QDesignerCustomWidgetInterface*> DesignerCustomWidgetCollectionInterface::customWidgets() const
{
	return m_widgetInterfaceList;
}

void DesignerCustomWidgetCollectionInterface::initData()
{
	QList<QPair<QString, QString>> pluginList;
	pluginList = FileUtility::scanPluginList(QString(PluginRootPath));
	for (const auto& [dllPath, jsonPath] : pluginList)
	{
		LibraryUtility::load(dllPath);
		LibraryUtility::getWidgetIdlist(dllPath);

		m_pluginDataMap = JsonUtility::analysis(FileUtility::readFile(jsonPath).toUtf8());

		for (auto& pluginData : m_pluginDataMap) {
			int typeId = QMetaType::type(pluginData->className.toUtf8());
			if (typeId != QMetaType::UnknownType)
			{
				m_widgetInterfaceList.push_back(new DesignerCustomWidgetInterface(this, pluginData));
			}
		}
	}
}