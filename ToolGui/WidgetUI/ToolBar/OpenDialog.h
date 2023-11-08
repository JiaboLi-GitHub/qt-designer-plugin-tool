#pragma once
#include <QDialog>
#include "ui_OpenDialog.h"
#include <QWidget>
#include <qfilesystemmodel.h>
#include <QDialog>

class OpenDialog : public QDialog
{
	Q_OBJECT

public:
	OpenDialog(QWidget* parent = nullptr);
	~OpenDialog();

	QString getPluginPath();

private:
	void initUI();
	void initSignalsSlots();

private:
	Ui::OpenDialogClass ui;
	QFileSystemModel* m_model = nullptr;
};
