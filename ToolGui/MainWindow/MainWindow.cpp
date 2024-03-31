#include "MainWindow.h"
#include <filesystem>
#include <QLibrary>
#include <QProcessEnvironment>
#include <QStatusBar>

#include "SharedLibrary/Utility/JsonUtility.h"
#include "SharedLibrary/Utility/FileUtility.h"
#include "SharedLibrary/Utility/LibraryUtility.h"
#include "WidgetManage/ToolTipManage.h"
#include "WidgetUI/SidebarWidget/TitleBarWidget.h"


constexpr char QtDirVariableName[] = "QTDIR";

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	initUI();
	initWidgetManage();
	initSignalsSlots();
}

MainWindow::~MainWindow()
{}

void MainWindow::initUI()
{
	this->setWindowIcon(QIcon(":/qtdesignerplugintool/LOGO.png"));
	this->setWindowTitle("拼图大师");

	ui.dockWidget->titleBarWidget()->deleteLater();
	ui.dockWidget->setTitleBarWidget(new TitleBarWidget(ui.dockWidget));

	QProcessEnvironment systemEnv = QProcessEnvironment::systemEnvironment();
	setupSlots(systemEnv.value(QString(QtDirVariableName)));
}

void MainWindow::initWidgetManage()
{
	ToolTipManage::initInstance(ui.centralWidgetMask);
	m_toolBarManage = new ToolBarManage(ui.toolBar, this);
	m_sidebarWidgetManage = new SidebarWidgetManage(ui.sidebarWidget, this);
	m_centralWidgetManage = new CentralWidgetManage(ui.centralWidget, this);
}

void MainWindow::initSignalsSlots()
{
	connect(m_toolBarManage, &ToolBarManage::openPluginSignals, this, &MainWindow::openPluginLibrarySlots);
	connect(m_toolBarManage, &ToolBarManage::closePluginSignals, this, &MainWindow::closePluginSlots);
	connect(m_toolBarManage, &ToolBarManage::savePluginSignals, this, &MainWindow::savePluginSlots);
	connect(m_toolBarManage, &ToolBarManage::setupSignals, this, &MainWindow::setupSlots);
	connect(m_toolBarManage, &ToolBarManage::matchSignals, this, &MainWindow::matchSlots);
	connect(m_sidebarWidgetManage, &SidebarWidgetManage::doubleClickedSignals, this, &MainWindow::openPluginSlots);
	connect(m_centralWidgetManage, &CentralWidgetManage::updateDataSignals, this, &MainWindow::updateDataSlots);
}

void MainWindow::initPluginLibraryData(const QList<int>& idList)
{
	for (auto id : idList)
	{
		QString className = QMetaType::typeName(id);
		if (m_pluginDataMap.contains(className))
		{
			m_pluginDataMap[className]->widget = (QWidget*)QMetaType::create(id);
		}
		else
		{
			auto pluginData = new PluginData();
			pluginData->className = className;

			QWidget* widget = (QWidget*)QMetaType::create(id);
			widget = widget ? widget : new QWidget();
			pluginData->widget = widget;

			m_pluginDataMap.insert(className, pluginData);
		}
	}

	m_sidebarWidgetManage->initModel(m_pluginDataMap);
}

void MainWindow::closePluginSlots()
{
	m_centralWidgetManage->clear();
	m_pluginDataMap.clear();
	m_sidebarWidgetManage->clear();

	for (auto pluginData : m_pluginDataMap)
	{
		delete pluginData->widget;
		delete pluginData;
	}
	LibraryUtility::unload(m_dllPath);
	m_pluginDataMap.clear();
	m_dllPath.clear();
	m_jsonPath.clear();
}

void MainWindow::savePluginSlots()
{
	QByteArray byteArray = JsonUtility::synthesis(m_pluginDataMap);
	bool ok = FileUtility::writeFile(m_jsonPath, byteArray);

	QString text = ok ? QStringLiteral("保存成功") : QStringLiteral("保存失败");
	ToolTipManage::showToolTip(text);
}

void MainWindow::openPluginSlots(const QString& className)
{
	m_centralWidgetManage->openPlugin(m_pluginDataMap[className]);
}

void MainWindow::setupSlots(QString qtPath)
{
	QStatusBar* statusBar = QMainWindow::statusBar();
	statusBar->showMessage(QStringLiteral("Qt路径：") + qtPath);
}

void MainWindow::matchSlots(QString path)
{
	QList<QString> classNameList = m_pluginDataMap.keys();
	QList<QString> hPathList;

	std::filesystem::path fsPath(path.toStdString());
	for (const auto& entry : std::filesystem::recursive_directory_iterator(fsPath))
	{
		if (entry.is_regular_file() && entry.path().extension() == ".h") {
			QString hPath = QString::fromStdString(entry.path().string());
			hPathList.append(std::move(hPath));
		}
	}

	for (auto& className : classNameList)
	{
		for (auto& hPath : hPathList)
		{
			QString destructorFunctionName = "~" + className;
			if (FileUtility::searchInFile(hPath, destructorFunctionName))
			{
				m_pluginDataMap[className]->includeFile = FileUtility::relativeFilePath(path, hPath);
				break;
			}

		}
	}

	m_centralWidgetManage->updateUI();
}

void MainWindow::updateDataSlots(const PluginData* m_pluginData)
{
	m_sidebarWidgetManage->updateData(m_pluginData);
}

void MainWindow::openPluginLibrarySlots(QString dllPath, QString jsonPath)
{
	m_jsonPath = jsonPath, m_dllPath = dllPath;

	m_pluginDataMap = JsonUtility::analysis(FileUtility::readFile(jsonPath).toLocal8Bit());

	LibraryUtility::load(dllPath);
	QList<int> idList = LibraryUtility::getWidgetIdlist(dllPath);
	initPluginLibraryData(idList);
}