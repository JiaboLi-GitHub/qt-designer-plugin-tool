#include "RegisterMetaType.h"

#include "qtmaterialautocomplete.h"
#include "qtmaterialcheckbox.h"
#include "qtmaterialflatbutton.h"

QList<int> registerMetaType()
{
	QList<int> idList;
	idList.append(qRegisterMetaType<QtMaterialAutoComplete>("QtMaterialAutoComplete"));
	idList.append(qRegisterMetaType<QtMaterialCheckBox>("QtMaterialCheckBox"));
	idList.append(qRegisterMetaType<QtMaterialFlatButton>("QtMaterialFlatButton"));
	return idList;
}
