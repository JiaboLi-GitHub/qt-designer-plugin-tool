#pragma once

#include <QObject>
#include <qbytearray.h>
#include "SharedLibrary/LibraryExport.h"
#include "SharedLibrary/Data/PluginLibraryData.h"

class SHARED_LIBRARY_API JsonUtility : public QObject
{
	Q_OBJECT

public:
	JsonUtility(QObject* parent = nullptr);
	~JsonUtility();

	static QMap<QString, PluginData*> analysis(const QByteArray& byteArray);
	static QByteArray synthesis(const QMap<QString, PluginData*> pluginDataMap);
};
