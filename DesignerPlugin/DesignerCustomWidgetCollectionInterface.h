#pragma once
#include <QtUiPlugin/QDesignerCustomWidgetCollectionInterface>

#include "SharedLibrary/Data/PluginLibraryData.h"

class  DesignerCustomWidgetCollectionInterface
	:public QObject, public QDesignerCustomWidgetCollectionInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "DesignerCustomWidgetCollectionInterface")
	Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)

public:
	DesignerCustomWidgetCollectionInterface(QObject* parent = nullptr);
	~DesignerCustomWidgetCollectionInterface();

	QList<QDesignerCustomWidgetInterface*> customWidgets() const override;

private:
	void initData();

private:
	QList<QDesignerCustomWidgetInterface*> m_widgetInterfaceList;
	QMap<QString, PluginData*> m_pluginDataMap;
};