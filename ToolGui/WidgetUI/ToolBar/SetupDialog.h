#pragma once

#include <QDialog>
#include "ui_SetupDialog.h"

class SetupDialog : public QDialog
{
	Q_OBJECT

public:
	SetupDialog(QWidget* parent = nullptr);
	~SetupDialog();

	QString getQtPath();

private:
	void initUI();
	void initSignalsSlots();

public slots:
	void setUseVariable(bool isUseVariable);
	void setUsePath(bool isUsePath);

private:
	Ui::SetupDialogClass ui;
};
