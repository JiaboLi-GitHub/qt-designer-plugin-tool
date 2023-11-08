#pragma once

#include <QWidget>
#include "../components/qtmaterialtextfield.h"
#include "../components/qtmaterialautocomplete.h"
#include "../components/qtmaterialcheckbox.h"
#include "../components/qtmaterialflatbutton.h"
#include "../components/qtmaterialraisedbutton.h"
#include "SharedLibrary/Data/PluginLibraryData.h"

class PluginDataWidget : public QWidget
{
	Q_OBJECT

public:
	PluginDataWidget(QWidget* parent = nullptr);
	~PluginDataWidget();

	void setPluginData(PluginData* pluginData);
	void updateUI();
	void clear();

private:
	void initUI();
	void initUINewWidget();
	void initUISetText();
	void initUILayout();
	void initSignalsSlots();
	void enabledWidget(bool isEnabled);

signals:
	void updateDataSignals(const PluginData* m_pluginData);

private slots:


private:
	QWidget* backgroundWidget = nullptr;
	QtMaterialTextField* m_nameWidget = nullptr;
	QtMaterialTextField* m_headFileWidget = nullptr;
	QtMaterialAutoComplete* m_groupWidget = nullptr;
	QtMaterialCheckBox* m_isContainerWidget = nullptr;
	QtMaterialFlatButton* m_iconWidget = nullptr;
	QtMaterialTextField* m_widthWidget = nullptr;
	QtMaterialTextField* m_heightWidget = nullptr;
	QtMaterialTextField* m_toolTipWidget = nullptr;
	QtMaterialTextField* m_whatsThisWidget = nullptr;
	QtMaterialRaisedButton* m_addPlugin = nullptr;
	QtMaterialRaisedButton* m_removePlugin = nullptr;

	PluginData* m_pluginData = nullptr;
};
