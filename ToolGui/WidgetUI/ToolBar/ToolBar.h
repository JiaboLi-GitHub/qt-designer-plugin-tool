#pragma once

#include <QToolBar>
#include <qtoolbutton.h>

#include "components/qtmaterialdialog.h"

class OpenPluginWidget;
class ToolBar : public QToolBar
{
	Q_OBJECT

public:
	ToolBar(QWidget* parent);
	~ToolBar();

	void setIsOpenPlugin(bool isOpenPlugin);

private:
	void initUI();
	void initSignalsSlots();

signals:
	void newPluginSignals(QString widgetDLLFilePath);
	void openPluginSignals(QString path);
	void closePluginSignals();
	void savePluginSignals();
	void installPluginSignals();
	void setupSignals(QString qtPath);
	void matchSignals(QString path);

public slots:
	void on_newBtn_clicked(bool checked = false);
	void on_openBtn_clicked(bool checked = false);
	void on_closeBtn_clicked(bool checked = false);
	void on_saveBtn_clicked(bool checked = false);
	void on_installBtn_clicked(bool checked = false);
	void on_setupBtn_clicked(bool checked = false);
	void on_matchBtn_clicked(bool checked = false);

	void openDialogFinished(int result);
	void setupDialogFinished(int result);
	void matchDialogFinished(int result);

private:
	QList<QToolButton**> m_btnList;
	QToolButton* m_newBtn = nullptr;
	QToolButton* m_openBtn = nullptr;
	QToolButton* m_saveBtn = nullptr;
	QToolButton* m_installBtn = nullptr;
	QToolButton* m_closeBtn = nullptr;
	QToolButton* m_setupBtn = nullptr;
	QToolButton* m_matchBtn = nullptr;
	bool m_isOpenPlugin = false;
};
