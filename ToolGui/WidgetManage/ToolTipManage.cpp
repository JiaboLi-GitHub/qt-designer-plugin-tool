#include "ToolTipManage.h"

QtMaterialSnackbar* ToolTipManage::m_toolTip = nullptr;

ToolTipManage::ToolTipManage(QObject* parent)
	: QObject(parent)
{}

ToolTipManage::~ToolTipManage()
{}

void ToolTipManage::initInstance(QWidget* parent)
{
	ToolTipManage::m_toolTip = new QtMaterialSnackbar(parent);
}

void ToolTipManage::showToolTip(const QString& text)
{
	if (ToolTipManage::m_toolTip)
	{
		ToolTipManage::m_toolTip->addMessage(text);
	}
}

