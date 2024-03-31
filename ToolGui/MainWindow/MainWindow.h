#pragma once

#include <QMainWindow>
#include <qlist.h>
#include "ui_MainWindow.h"
#include "SharedLibrary/Data/PluginLibraryData.h"

#include "WidgetManage/ToolBarManage.h"
#include "WidgetManage/SidebarWidgetManage.h"
#include "WidgetManage/CentralWidgetManage.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private:
	void initUI();
	void initWidgetManage();
	void initSignalsSlots();
	void initPluginLibraryData(const QList<int>& idList);

public slots:
	void openPluginLibrarySlots(QString dllPath, QString jsonPath);
	void closePluginSlots();
	void savePluginSlots();
	void openPluginSlots(const QString& className);
	void setupSlots(QString qtPath);
	void matchSlots(QString path);
	void updateDataSlots(const PluginData* m_pluginData);

private:
	Ui::MainWindowClass ui;
	QMap<QString, PluginData*> m_pluginDataMap;
	QString m_jsonPath;
	QString m_dllPath;

	ToolBarManage* m_toolBarManage = nullptr;
	SidebarWidgetManage* m_sidebarWidgetManage = nullptr;
	CentralWidgetManage* m_centralWidgetManage = nullptr;
};
