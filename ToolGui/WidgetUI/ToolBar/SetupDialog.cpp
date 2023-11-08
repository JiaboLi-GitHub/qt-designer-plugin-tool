#include "SetupDialog.h"
#include <QProcessEnvironment>
constexpr char DefaultVariableName[] = "QTDIR";

SetupDialog::SetupDialog(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	initUI();
	initSignalsSlots();
}

SetupDialog::~SetupDialog()
{}

QString SetupDialog::getQtPath()
{
	QString qtPath;
	if (ui.variableCheckBox->isChecked())
	{
		QProcessEnvironment systemEnv = QProcessEnvironment::systemEnvironment();
		qtPath = systemEnv.value(ui.variableLineEdit->text());
	}
	else
	{
		qtPath = ui.pathLineEdit->text();
	}

	return qtPath;
}

void SetupDialog::initUI()
{
	setUseVariable(true);
	ui.variableLineEdit->setText(QString(DefaultVariableName));
}

void SetupDialog::initSignalsSlots()
{
	connect(ui.variableCheckBox, &QAbstractButton::clicked, this, &SetupDialog::setUseVariable);
	connect(ui.pathCheckBox, &QAbstractButton::clicked, this, &SetupDialog::setUsePath);
	connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
	connect(ui.buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

void SetupDialog::setUseVariable(bool isUseVariable)
{
	ui.variableCheckBox->setChecked(isUseVariable);
	ui.variableLineEdit->setEnabled(isUseVariable);

	ui.pathCheckBox->setChecked(!isUseVariable);
	ui.pathLineEdit->setEnabled(!isUseVariable);
}

void SetupDialog::setUsePath(bool isUsePath)
{
	setUseVariable(!isUsePath);
}