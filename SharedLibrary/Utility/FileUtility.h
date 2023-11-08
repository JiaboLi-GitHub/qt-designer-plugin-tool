#pragma once

#include <QObject>
#include <QByteArray>
#include "SharedLibrary/LibraryExport.h"

class SHARED_LIBRARY_API FileUtility : public QObject
{
	Q_OBJECT

public:
	FileUtility(QObject* parent);
	~FileUtility();

	static QString readFile(const QString& filePath);
	static bool writeFile(const QString& filePath, const QByteArray& byteArray);
	static QList<QPair<QString, QString>> scanPluginList(const QString& path);
	static QString getPluginLibraryRootPath();	//获存放插件库的根路径
	static bool searchInFile(const QString& filePath, const QString& searchText);
	static QString relativeFilePath(const QString& pathA, const QString& pathB);
};
