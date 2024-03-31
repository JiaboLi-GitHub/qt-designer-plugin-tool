#include <QtWidgets/QApplication>

#include "MainWindow/MainWindow.h"
#include "SharedLibrary/Utility/FileUtility.h"

#include <QFontDatabase>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	MainWindow mainWindow;
	mainWindow.setStyleSheet(FileUtility::readFile(":/qtdesignerplugintool/GlobalStyle.qss"));

	// 加载字体文件
	int id = QFontDatabase::addApplicationFont(":/qtdesignerplugintool/AlimamaDongFangDaKai-Regular.ttf");
	if (id != -1) {
		// 根据文件中的字体名称创建字体对象
		QString fontName = QFontDatabase::applicationFontFamilies(id).at(0);
		QFont font(fontName, 12);
		mainWindow.setFont(font);
	}

	mainWindow.show();
	return a.exec();
}
