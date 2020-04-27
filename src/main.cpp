#include <QApplication>

#include "include/Matrix.h"

int main(int argc, char** argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	QApplication app(argc, argv);

	Matrix matrix;
	matrix.show();

	return QApplication::exec();
}
