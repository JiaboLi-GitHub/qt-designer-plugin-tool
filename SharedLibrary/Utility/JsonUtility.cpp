#include "JsonUtility.h"

#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include <qjsonvalue.h>

JsonUtility::JsonUtility(QObject* parent)
	: QObject(parent)
{}

JsonUtility::~JsonUtility()
{}

QMap<QString, PluginData*> JsonUtility::analysis(const QByteArray& byteArray)
{
	QMap<QString, PluginData*> pluginDataMap;

	auto documentJson = QJsonDocument::fromJson(byteArray);
	for (const auto& pluginDataObjectJson : documentJson.array())
	{
		auto pluginDataJson = pluginDataObjectJson.toObject();

		PluginData* pluginData = new PluginData();
		pluginData->isPack = pluginDataJson["IsPack"].toBool();
		pluginData->className = pluginDataJson["ClassName"].toString();
		pluginData->objectName = pluginDataJson["ObjectName"].toString();
		pluginData->isContainer = pluginDataJson["IsContainer"].toBool();
		pluginData->icon = pluginDataJson["Icon"].toString();
		pluginData->group = pluginDataJson["Group"].toString();
		pluginData->includeFile = pluginDataJson["IncludeFile"].toString();
		pluginData->toolTip = pluginDataJson["ToolTip"].toString();
		pluginData->whatsThis = pluginDataJson["WhatsThis"].toString();
		pluginData->width = pluginDataJson["Width"].toInt();
		pluginData->height = pluginDataJson["Height"].toInt();
		pluginData->isExtension = pluginDataJson["isExtension"].toBool();

		pluginDataMap.insert(pluginData->className, pluginData);
	}

	return pluginDataMap;
}

QByteArray JsonUtility::synthesis(const QMap<QString, PluginData*> pluginDataMap)
{
	QJsonArray jsonArray;

	for (const auto& pluginData : pluginDataMap) {
		QJsonObject pluginDataJson;
		pluginDataJson["IsPack"] = pluginData->isPack;
		pluginDataJson["ClassName"] = pluginData->className;
		pluginDataJson["ObjectName"] = pluginData->objectName;
		pluginDataJson["IsContainer"] = pluginData->isContainer;
		pluginDataJson["Icon"] = pluginData->icon;
		pluginDataJson["Group"] = pluginData->group;
		pluginDataJson["IncludeFile"] = pluginData->includeFile;
		pluginDataJson["ToolTip"] = pluginData->toolTip;
		pluginDataJson["WhatsThis"] = pluginData->whatsThis;
		pluginDataJson["Width"] = pluginData->width;
		pluginDataJson["Height"] = pluginData->height;
		pluginDataJson["isExtension"] = pluginData->isExtension;

		jsonArray.append(pluginDataJson);
	}

	QJsonDocument document(jsonArray);
	return document.toJson();
}
