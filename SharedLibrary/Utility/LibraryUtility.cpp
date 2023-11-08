#include "LibraryUtility.h"

QMap<QString, QLibrary*> LibraryUtility::m_libraryMap = QMap<QString, QLibrary*>();

typedef QList<int>(*RegisterMetaType)(void);
constexpr const char* FunctionIdentifying = "?registerMetaType@@YA?AV?$QList@H@@XZ";

LibraryUtility::LibraryUtility(QObject* parent)
	: QObject(parent)
{}

LibraryUtility::~LibraryUtility()
{}

void LibraryUtility::load(QString path)
{
	if (!m_libraryMap.contains(path))
	{
		auto library = new QLibrary(path);
		library->load();
		m_libraryMap.insert(path, library);
	}
}

QList<int> LibraryUtility::getWidgetIdlist(QString path)
{
	QList<int> idList;
	if (m_libraryMap.contains(path))
	{
		auto library = m_libraryMap[path];
		RegisterMetaType registerMetaType = (RegisterMetaType)library->resolve(FunctionIdentifying);
		if (registerMetaType)
			idList = registerMetaType();
	}
	return idList;
}

void LibraryUtility::unload(QString path)
{
	if (m_libraryMap.contains(path))
	{
		auto library = m_libraryMap[path];
		library->unload();
		library->deleteLater();
		m_libraryMap.remove(path);
	}
}
