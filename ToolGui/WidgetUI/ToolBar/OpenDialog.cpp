#include "OpenDialog.h"
#include "SharedLibrary/Utility/FileUtility.h"

OpenDialog::OpenDialog(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	initUI();
	initSignalsSlots();
}

OpenDialog::~OpenDialog()
{}

QString OpenDialog::getPluginPath()
{
	QModelIndex modelIndex = ui.listView->currentIndex();
	return m_model->filePath(modelIndex);
}

void OpenDialog::initUI()
{
	auto pluginLibraryRootPath = FileUtility::getPluginLibraryRootPath();

	m_model = new QFileSystemModel(this);
	m_model->setRootPath(pluginLibraryRootPath);

	ui.listView->setModel(m_model);
	ui.listView->setRootIndex(m_model->index(pluginLibraryRootPath));
}

void OpenDialog::initSignalsSlots()
{
	connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
	connect(ui.buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}
