#include "ToolBarManage.h"
#include <qcoreapplication.h>
#include <QFileInfo>
#include <qdir.h>
#include <QProcessEnvironment>
#include "WidgetManage/ToolTipManage.h"
#include "SharedLibrary/Utility/FileUtility.h"

constexpr char QtDirVariableName[] = "QTDIR";

#include <qdebug.h>


ToolBarManage::ToolBarManage(ToolBar* toolBar, QObject* parent)
	: QObject(parent), m_toolBar(toolBar)
{
	initSignalsSlots();
	initQtDir();
}

ToolBarManage::~ToolBarManage()
{}

void ToolBarManage::initQtDir()
{
	QProcessEnvironment systemEnv = QProcessEnvironment::systemEnvironment();
	m_qtDir = systemEnv.value(QString(QtDirVariableName));
}

void ToolBarManage::initSignalsSlots()
{
	connect(m_toolBar, &ToolBar::newPluginSignals, this, &ToolBarManage::newPluginSlots);
	connect(m_toolBar, &ToolBar::openPluginSignals, this, &ToolBarManage::openPluginSlots);
	connect(m_toolBar, &ToolBar::closePluginSignals, this, &ToolBarManage::closePluginSlots);
	connect(m_toolBar, &ToolBar::savePluginSignals, this, &ToolBarManage::savePluginSlots);
	connect(m_toolBar, &ToolBar::installPluginSignals, this, &ToolBarManage::installPluginSlots);
	connect(m_toolBar, &ToolBar::setupSignals, this, &ToolBarManage::setupSlots);
	connect(m_toolBar, &ToolBar::matchSignals, this, &ToolBarManage::matchSlots);
}

void ToolBarManage::newPluginSlots(QString widgetDLLFilePath)
{
	if (m_isOpenPlugin)
	{
		ToolTipManage::showToolTip(QStringLiteral("已打开插件库，请先关闭"));
		return;
	}

	m_pluginName = QFileInfo(widgetDLLFilePath).baseName();
	QString pluginDLLPath = FileUtility::getPluginLibraryRootPath() + "/" + m_pluginName;
	QString pluginDLLFilePath = pluginDLLPath + "/" + QFileInfo(widgetDLLFilePath).fileName();
	QString pluginJsonFilePath = pluginDLLPath + "/" + QFileInfo(widgetDLLFilePath).baseName() + ".json";

	QDir dir;
	bool ok = true;
	if (dir.mkpath(pluginDLLPath))
	{
		//清除同名文件
		if (QFile::exists(pluginDLLFilePath))
			ok &= QFile::remove(pluginDLLFilePath);
		if (QFile::exists(pluginJsonFilePath))
			ok &= QFile::remove(pluginJsonFilePath);

		//拷贝控件动态库
		ok &= QFile::copy(widgetDLLFilePath, pluginDLLFilePath);
		//新建json
		QFile file(pluginJsonFilePath);
		if (file.open(QIODevice::ReadWrite))
			file.close();
		else
			ok = false;
	}

	QString text = ok ? QStringLiteral("新建插件库成功") : QStringLiteral("新建插件库失败");
	ToolTipManage::showToolTip(text);

	if (ok)
	{
		emit openPluginSignals(pluginDLLFilePath, pluginJsonFilePath);
		m_isOpenPlugin = true;
	}
}

void ToolBarManage::openPluginSlots(QString path)
{
	if (m_isOpenPlugin)
	{
		ToolTipManage::showToolTip(QStringLiteral("已打开插件库，请先关闭"));
		return;
	}

	m_pluginName = QFileInfo(path).baseName();
	m_dllPath = path + "/" + m_pluginName + ".dll";
	m_jsonPath = path + "/" + m_pluginName + ".json";

	bool ok = QFile::exists(m_dllPath) && QFile::exists(m_jsonPath);

	QString text = ok ? QStringLiteral("打开插件库成功") : QStringLiteral("打开插件库失败");
	ToolTipManage::showToolTip(text);

	if (ok)
	{
		emit openPluginSignals(m_dllPath, m_jsonPath);
		m_isOpenPlugin = true;
	}
}

void ToolBarManage::closePluginSlots()
{
	if (!m_isOpenPlugin)
	{
		ToolTipManage::showToolTip(QStringLiteral("未打开插件库"));
		return;
	}

	emit closePluginSignals();

	ToolTipManage::showToolTip(QStringLiteral("关闭成功"));
	m_isOpenPlugin = false;
}

void ToolBarManage::savePluginSlots()
{
	if (!m_isOpenPlugin)
	{
		ToolTipManage::showToolTip(QStringLiteral("未打开插件库"));
		return;
	}

	emit savePluginSignals();
}

void ToolBarManage::installPluginSlots()
{
	if (!m_isOpenPlugin)
	{
		ToolTipManage::showToolTip(QStringLiteral("未打开插件库"));
		return;
	}

	QString qtDesignerPath = m_qtDir + "/plugins/designer";
	QString designerDataPath = qtDesignerPath + "/DesignerData/" + m_pluginName;
	QString designerPluginPath = QCoreApplication::applicationDirPath() + "/DesignerPlugin.dll";
	QString sharedLibraryPath = QCoreApplication::applicationDirPath() + "/SharedLibrary.dll";
	QString newDllPath = designerDataPath + "/" + m_pluginName + ".dll";
	QString newJsonPath = designerDataPath + "/" + m_pluginName + ".json";
	QString newDesignerPluginPath = qtDesignerPath + "/DesignerPlugin.dll";
	QString newSharedLibraryPath = qtDesignerPath + "/SharedLibrary.dll";
	QDir pluginDataDir(designerDataPath);

	bool ok = true;
	if (!pluginDataDir.exists())
	{
		ok &= pluginDataDir.mkpath(".");
	}
	//清除同名文件
	if (QFile::exists(newJsonPath))
		ok &= QFile::remove(newJsonPath);
	if (QFile::exists(newDllPath))
		ok &= QFile::remove(newDllPath);
	if (QFile::exists(newDesignerPluginPath))
		ok &= QFile::remove(newDesignerPluginPath);
	if (QFile::exists(newSharedLibraryPath))
		ok &= QFile::remove(newSharedLibraryPath);
	ok &= QFile::copy(m_jsonPath, newJsonPath);
	ok &= QFile::copy(m_dllPath, newDllPath);
	ok &= QFile::copy(designerPluginPath, newDesignerPluginPath);
	ok &= QFile::copy(sharedLibraryPath, newSharedLibraryPath);

	QString text = ok ? QStringLiteral("安装成功") : QStringLiteral("安装失败");
	ToolTipManage::showToolTip(text);
}


void ToolBarManage::setupSlots(QString qtPath)
{
	emit setupSignals(qtPath);
}

void ToolBarManage::matchSlots(QString path)
{
	if (!m_isOpenPlugin)
	{
		ToolTipManage::showToolTip(QStringLiteral("未打开插件库"));
		return;
	}

	emit matchSignals(path);

	ToolTipManage::showToolTip(QStringLiteral("匹配成功"));
}

