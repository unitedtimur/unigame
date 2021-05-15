#include <QApplication>
#include <QTimer>
#include <QSound>

#include "../include/SplashCompany.h"
#include "include/Matrix.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    SplashCompany splashScreen;
    splashScreen.setPixmap(QPixmap(":/img/images/splash.png"));
    splashScreen.show();

    QEventLoop loop;
    QSound::play("qrc:/sounds/sounds/SPLASH_LOAD.wav");
    QTimer::singleShot(5000, &loop, &QEventLoop::quit);
    loop.exec();

    Matrix matrix;
    matrix.show();

    splashScreen.finish(&matrix);

    return app.exec();
}
