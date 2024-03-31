#include "DesignerCustomWidgetInterface.h"

DesignerCustomWidgetInterface::DesignerCustomWidgetInterface(QObject* parent, PluginData* pluginData)
{
	m_pluginData.reset(pluginData);
	initialized = false;
}

DesignerCustomWidgetInterface::~DesignerCustomWidgetInterface()
{
}

void DesignerCustomWidgetInterface::initialize(QDesignerFormEditorInterface* formEditor)
{
	if (initialized)
		return;
	initialized = true;
}

bool DesignerCustomWidgetInterface::isInitialized() const
{
	return initialized;
}

QWidget* DesignerCustomWidgetInterface::createWidget(QWidget* parent)
{
	int typeId = QMetaType::type(m_pluginData->className.toUtf8());
	auto widget = (QWidget*)QMetaType::create(typeId);
	widget->setParent(parent);
	return widget;
}

QString DesignerCustomWidgetInterface::name() const
{
	return m_pluginData->className;
}

QString DesignerCustomWidgetInterface::group() const
{
	return m_pluginData->group;
}

QIcon DesignerCustomWidgetInterface::icon() const
{
	return QIcon(m_pluginData->icon);
}

QString DesignerCustomWidgetInterface::toolTip() const
{
	return m_pluginData->toolTip;
}

QString DesignerCustomWidgetInterface::whatsThis() const
{
	return m_pluginData->whatsThis;
}

bool DesignerCustomWidgetInterface::isContainer() const
{
	return m_pluginData->isContainer;
}

QString DesignerCustomWidgetInterface::domXml() const
{
	QString xml = "<widget class=\"%1\" name=\"%2\">                              \n\
				   	  <property name=\"geometry\">                                \n\
                          <rect>                                                  \n\
						    	<width>%3</width>                                 \n\
						    	<height>%4</height>                               \n\
						  </rect>                                                 \n\
					  </property>                                                 \n\
                   </widget>                                                      \n";
	xml = xml.arg(m_pluginData->className).arg(m_pluginData->objectName).arg(m_pluginData->width).arg(m_pluginData->height);
	return xml;
}

QString DesignerCustomWidgetInterface::includeFile() const
{
	return m_pluginData->includeFile;
}
