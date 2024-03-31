#pragma once

#include <QObject>
#include "WidgetUI/ToolBar/ToolBar.h"

#include "components/qtmaterialsnackbar.h"
class ToolBarManage : public QObject
{
	Q_OBJECT

public:
	ToolBarManage(ToolBar* toolBar, QObject* parent);
	~ToolBarManage();


private:
	void initQtDir();
	void initSignalsSlots();


signals:
	void openPluginSignals(QString dllPath, QString jsonPath);
	void closePluginSignals();
	void savePluginSignals();
	void setupSignals(QString qtPath);
	void matchSignals(QString path);

public slots:
	void newPluginSlots(QString widgetDLLFilePath);
	void openPluginSlots(QString path);
	void closePluginSlots();
	void savePluginSlots();
	void installPluginSlots();
	void setupSlots(QString qtPath);
	void matchSlots(QString path);

private:
	ToolBar* m_toolBar = nullptr;
	QString m_pluginName;
	QString m_jsonPath;
	QString m_dllPath;
	QString m_qtDir;
	bool m_isOpenPlugin = false;
};
