#ifndef QTMATERIALRAISEDBUTTON_H
#define QTMATERIALRAISEDBUTTON_H

#include "qtmaterialflatbutton.h"
#include "SharedExport.h"
class QtMaterialRaisedButtonPrivate;

class MATERIAL_WIDGET_API QtMaterialRaisedButton : public QtMaterialFlatButton
{
	Q_OBJECT

public:
	explicit QtMaterialRaisedButton(QWidget* parent = 0);
	explicit QtMaterialRaisedButton(const QString& text, QWidget* parent = 0);
	~QtMaterialRaisedButton();

protected:
	QtMaterialRaisedButton(QtMaterialRaisedButtonPrivate& d, QWidget* parent = 0);

	bool event(QEvent* event) Q_DECL_OVERRIDE;

private:
	Q_DISABLE_COPY(QtMaterialRaisedButton)
		Q_DECLARE_PRIVATE(QtMaterialRaisedButton)
};

#endif // QTMATERIALRAISEDBUTTON_H
