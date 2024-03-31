#include "MatchDialog.h"

#include <QFileDialog>
#include <qdebug.h>

MatchDialog::MatchDialog(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	initUI();
	initSignalsSlots();
}

MatchDialog::~MatchDialog()
{}

QString MatchDialog::getPath()
{
	return ui.pathLineEdit->text();
}

void MatchDialog::initUI()
{
}

void MatchDialog::initSignalsSlots()
{
	connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
	connect(ui.buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

void MatchDialog::on_fileDialogBt_clicked(bool checked)
{
	QString defaultPath = QApplication::applicationDirPath();

	QFileDialog dialog;
	dialog.setFileMode(QFileDialog::Directory);
	dialog.setOption(QFileDialog::ShowDirsOnly);
	dialog.setDirectory(defaultPath);
	dialog.setWindowTitle("请选择头文件根路径");

	if (dialog.exec()) {
		QStringList selectedDirectories = dialog.selectedFiles();
		ui.pathLineEdit->setText(selectedDirectories[0]);
	}
}