#include <QApplication>
#include <QTimer>
#include <QSound>
#include <QTranslator>
#include <QUrl>
#include <QDebug>

#include "../include/SplashCompany.h"
#include "include/Matrix.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

//    QTranslator qtLanguageTranslator;
//    qDebug() << qtLanguageTranslator.load(QUrl(":/translate/unigame_en.qm").toString());
//    qApp->installTranslator(&qtLanguageTranslator);

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
