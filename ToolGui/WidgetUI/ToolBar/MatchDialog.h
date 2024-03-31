#pragma once

#include <QDialog>
#include "ui_MatchDialog.h"

class MatchDialog : public QDialog
{
	Q_OBJECT

public:
	MatchDialog(QWidget* parent = nullptr);
	~MatchDialog();

	QString getPath();

private:
	void initUI();
	void initSignalsSlots();

public slots:
	void on_fileDialogBt_clicked(bool checked);

private:
	Ui::MatchDialogClass ui;
};
