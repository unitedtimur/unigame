#include <QApplication>
#include "include/UniMainWindow.h"

int main(int argc, char** argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	QApplication app(argc, argv);

	UniMainWindow test;

	test.show();

	return app.exec();
}
