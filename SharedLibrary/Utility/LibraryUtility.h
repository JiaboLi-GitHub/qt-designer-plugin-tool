#pragma once

#include <QObject>
#include <QLibrary>
#include <qlist.h>
#include <qmap.h>
#include "SharedLibrary/LibraryExport.h"

class SHARED_LIBRARY_API LibraryUtility : public QObject
{
	Q_OBJECT

public:
	LibraryUtility(QObject* parent);
	~LibraryUtility();

	static void load(QString path);
	static QList<int> getWidgetIdlist(QString path);
	static void unload(QString path);

private:
	static QMap<QString, QLibrary*> m_libraryMap;
};
