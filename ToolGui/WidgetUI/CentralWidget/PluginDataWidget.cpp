#include "PluginDataWidget.h"

#include <QHBoxLayout>
#include <qapplication.h>
#include <qstyle.h>
#include <QLabel>
#include <qdebug.h>

PluginDataWidget::PluginDataWidget(QWidget* parent)
	: QWidget(parent)
{
	initUI();
	initSignalsSlots();
	enabledWidget(false);
}

PluginDataWidget::~PluginDataWidget()
{}

void PluginDataWidget::setPluginData(PluginData* pluginData)
{
	m_pluginData = pluginData;
	enabledWidget(true);
	updateUI();
}

void PluginDataWidget::clear()
{
	m_nameWidget->clear();
	m_headFileWidget->clear();
	m_groupWidget->clear();
	m_widthWidget->clear();
	m_heightWidget->clear();
	m_toolTipWidget->clear();
	//	m_whatsThisWidget->clear();
	m_isContainerWidget->setChecked(false);
	m_iconWidget->setChecked(false);
	enabledWidget(false);
	m_pluginData = nullptr;
}

void PluginDataWidget::initUI()
{
	//白色背景
	this->setMinimumSize(600, 200);
	backgroundWidget = new QWidget(this);
	backgroundWidget->setStyleSheet("background-color: white;");
	QHBoxLayout* hBoxLayout = new QHBoxLayout(this);
	hBoxLayout->setContentsMargins(0, 0, 0, 0);
	hBoxLayout->addWidget(backgroundWidget);
	this->setLayout(hBoxLayout);

	initUINewWidget();
	initUISetText();
	initUILayout();
}

void PluginDataWidget::initUINewWidget()
{
	m_nameWidget = new QtMaterialTextField(this);
	m_headFileWidget = new QtMaterialTextField(this);
	m_groupWidget = new QtMaterialAutoComplete(this);
	m_isContainerWidget = new QtMaterialCheckBox(this);
	m_iconWidget = new QtMaterialFlatButton(this);
	m_toolTipWidget = new QtMaterialTextField(this);
	//m_whatsThisWidget = new QtMaterialTextField(this);
	m_widthWidget = new QtMaterialTextField(this);
	m_heightWidget = new QtMaterialTextField(this);
	m_addPlugin = new QtMaterialRaisedButton(this);
	m_removePlugin = new QtMaterialRaisedButton(this);
	m_addPlugin->setBackgroundColor(QColor("#00bcd4"));
	m_addPlugin->setFixedSize(80, 30);
	m_removePlugin->setBackgroundColor(QColor("#dddddd"));
	m_removePlugin->setFixedSize(80, 30);
}

void PluginDataWidget::initUISetText()
{
	m_nameWidget->setLabel("Name *");
	m_headFileWidget->setLabel("IncludeFile *");
	m_groupWidget->setLabel("Group *");
	m_isContainerWidget->setText("IsContainer *");
	m_iconWidget->setText("Icon");
	m_iconWidget->setIcon(QApplication::style()->standardIcon((enum QStyle::StandardPixmap)0));

	m_iconWidget->setRole(Material::Primary);
	m_iconWidget->setUseThemeColors(false);
	m_widthWidget->setLabel("Width");
	m_heightWidget->setLabel("Height");
	m_toolTipWidget->setLabel("ToolTip");
	//m_whatsThisWidget->setLabel("WhatsThis");
	m_addPlugin->setText("添加");
	m_removePlugin->setText("移除");
}

void PluginDataWidget::initUILayout()
{
	QHBoxLayout* hBoxLayout1 = new QHBoxLayout(this);
	QHBoxLayout* hBoxLayout2 = new QHBoxLayout(this);
	QHBoxLayout* hBoxLayout3 = new QHBoxLayout(this);

	hBoxLayout1->addWidget(m_nameWidget, 1);
	hBoxLayout1->addWidget(m_groupWidget, 1);
	hBoxLayout1->addWidget(m_headFileWidget, 3);

	hBoxLayout2->addWidget(m_isContainerWidget, 0);
	hBoxLayout2->addWidget(m_iconWidget, 0);
	hBoxLayout2->addWidget(m_widthWidget, 1);
	hBoxLayout2->addWidget(m_heightWidget, 1);
	hBoxLayout2->addWidget(m_toolTipWidget, 2);

	QSpacerItem* spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	hBoxLayout3->addSpacerItem(spacer);
	hBoxLayout3->addWidget(m_addPlugin);
	hBoxLayout3->addWidget(m_removePlugin);

	QVBoxLayout* vBoxLayout = new QVBoxLayout(this);
	vBoxLayout->addLayout(hBoxLayout1);
	vBoxLayout->addLayout(hBoxLayout2);
	vBoxLayout->addLayout(hBoxLayout3);

	backgroundWidget->setLayout(vBoxLayout);
}

void PluginDataWidget::initSignalsSlots()
{
	connect(m_nameWidget, &QLineEdit::editingFinished, this, [this] {
		m_pluginData->objectName = m_nameWidget->text();
		emit updateDataSignals(m_pluginData);
		});
	connect(m_headFileWidget, &QLineEdit::editingFinished, this, [this] {
		m_pluginData->includeFile = m_headFileWidget->text();
		});
	connect(m_groupWidget, &QLineEdit::editingFinished, this, [this] {
		m_pluginData->group = m_groupWidget->text();
		});
	connect(m_widthWidget, &QLineEdit::editingFinished, this, [this] {
		m_pluginData->width = m_widthWidget->text().toInt();
		});
	connect(m_heightWidget, &QLineEdit::editingFinished, this, [this] {
		m_pluginData->height = m_heightWidget->text().toInt();
		});
	connect(m_toolTipWidget, &QLineEdit::editingFinished, this, [this] {
		m_pluginData->toolTip = m_toolTipWidget->text();
		});
	connect(m_isContainerWidget, &QAbstractButton::toggled, this, [this](bool checked) {
		m_pluginData->isContainer = checked;
		});
	connect(m_addPlugin, &QAbstractButton::clicked, this, [this](bool checked) {
		m_pluginData->isPack = m_pluginData->isExtension = true;
		emit updateDataSignals(m_pluginData);
		});
	connect(m_removePlugin, &QAbstractButton::clicked, this, [this](bool checked) {
		m_pluginData->isPack = m_pluginData->isExtension = false;
		emit updateDataSignals(m_pluginData);
		});
}

void PluginDataWidget::updateUI()
{
	if (m_pluginData == nullptr)
		return;

	m_nameWidget->setText(m_pluginData->objectName);
	m_headFileWidget->setText(m_pluginData->includeFile);
	m_groupWidget->setText(m_pluginData->group);
	m_isContainerWidget->setChecked(m_pluginData->isContainer);
	m_iconWidget->setIcon(QIcon(m_pluginData->icon));
	m_widthWidget->setText(QString::number(m_pluginData->width));
	m_heightWidget->setText(QString::number(m_pluginData->height));
	m_toolTipWidget->setText(m_pluginData->toolTip);
}

void PluginDataWidget::enabledWidget(bool isEnabled)
{
	auto objectList = this->children();
	for (auto& object : objectList)
	{
		auto widget = qobject_cast<QWidget*>(object);
		if (widget)
		{
			widget->setEnabled(isEnabled);
		}
	}
}

