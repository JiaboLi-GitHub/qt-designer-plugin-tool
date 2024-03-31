#pragma once
#include <QObject>
#include <qwidget.h>

struct PluginData
{
	QWidget* widget;
	bool isPack;
	QString objectName;
	QString className;
	bool isContainer;
	QString icon;
	QString group;
	QString includeFile;
	QString toolTip;
	QString whatsThis;
	int width;
	int height;
	bool isExtension;

	PluginData()
	{
		widget = nullptr;
		isPack = false;
		isContainer = false;
		width = 100;
		height = 100;
		isExtension = false;
		group = QStringLiteral("customize");
	}

	PluginData(const PluginData& other)
	{
		widget = other.widget;
		isPack = other.isPack;
		objectName = other.objectName;
		className = other.className;
		isContainer = other.isContainer;
		icon = other.icon;
		group = other.group;
		includeFile = other.includeFile;
		toolTip = other.toolTip;
		whatsThis = other.whatsThis;
		width = other.width;
		height = other.height;
		isExtension = other.isExtension;
	}

	void operator=(const PluginData& other)
	{
		widget = other.widget;
		isPack = other.isPack;
		objectName = other.objectName;
		className = other.className;
		isContainer = other.isContainer;
		icon = other.icon;
		group = other.group;
		includeFile = other.includeFile;
		toolTip = other.toolTip;
		whatsThis = other.whatsThis;
		width = other.width;
		height = other.height;
		isExtension = other.isExtension;
	}
};