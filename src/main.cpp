#include <QApplication>

#include "include/UniMainWindow.h"
#include "include/Matrix.h"

//#include <SFML/Graphics.hpp>

int main(int argc, char** argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	QApplication app(argc, argv);

	//UniMainWindow test;
	//
	//test.show();
	
	Matrix matrix;
	matrix.show();

	return QApplication::exec();
}
