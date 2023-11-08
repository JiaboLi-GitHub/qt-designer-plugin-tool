#pragma once
#include <QObject>
#include <QtUiPlugin/QDesignerCustomWidgetInterface>
#include <memory>

#include "SharedLibrary/Data/PluginLibraryData.h"

class DesignerCustomWidgetInterface : public QObject, public QDesignerCustomWidgetInterface
{
	Q_OBJECT
		Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
	DesignerCustomWidgetInterface(QObject* parent, PluginData* pluginData);
	~DesignerCustomWidgetInterface();

	bool isContainer() const override;
	bool isInitialized() const override;
	QIcon icon() const override;
	QString domXml() const override;
	QString group() const override;
	QString includeFile() const override;
	QString name() const override;
	QString toolTip() const override;
	QString whatsThis() const override;
	QWidget* createWidget(QWidget* parent) override;
	void initialize(QDesignerFormEditorInterface* core) override;

private:
	bool initialized;
	std::shared_ptr<PluginData> m_pluginData;
};
