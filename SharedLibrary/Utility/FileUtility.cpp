#include "FileUtility.h"

#include <qfile.h>
#include <qtextstream.h>
#include <qcoreapplication.h>
#include <qdir.h>

FileUtility::FileUtility(QObject* parent)
	: QObject(parent)
{}

FileUtility::~FileUtility()
{}

QString FileUtility::readFile(const QString& filePath)
{
	QString text;
	QFile file(filePath);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream stream(&file);
		text = stream.readAll();
	}
	return text;
}

bool FileUtility::writeFile(const QString& filePath, const QByteArray& byteArray)
{
	QFile file(filePath);
	if (file.open(QIODevice::WriteOnly))
	{
		file.write(byteArray);
		file.close();
		return true;
	}

	return false;
}

QList<QPair<QString, QString>> FileUtility::scanPluginList(const QString& path)
{
	QList<QPair<QString, QString>> pluginList;

	QDir dir(path);
	QStringList entries = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
	for (auto& dirName : entries)
	{
		QString pluginPath = path + "/" + dirName;
		QString dllPath = pluginPath + "/" + dirName + ".dll";
		QString jsonPath = pluginPath + "/" + dirName + ".json";
		if (QFile::exists(dllPath) && QFile::exists(jsonPath))
			pluginList.emplace_back(dllPath, jsonPath);
	}

	return pluginList;
}

QString FileUtility::getPluginLibraryRootPath()
{
	const QString path = QCoreApplication::applicationDirPath() + "/PluginLibrary";
	QDir dir(path);
	if (!dir.exists())
		dir.mkpath(path);

	return QCoreApplication::applicationDirPath() + "/PluginLibrary";
}

bool FileUtility::searchInFile(const QString& filePath, const QString& searchText)
{
	QFile file(filePath);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QTextStream in(&file);
		while (!in.atEnd()) {
			QString line = in.readLine();
			if (line.contains(searchText)) {
				file.close();
				return true;
			}
		}
		file.close();
	}
	return false;
}

QString FileUtility::relativeFilePath(const QString& pathA, const QString& pathB)
{
	QDir dir(pathA);
	return dir.relativeFilePath(pathB);
}
