#include <QApplication>

#include "include/Matrix.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	Matrix matrix;
	matrix.show();

	return QApplication::exec();
}
