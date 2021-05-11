#ifndef SPLASHCOMPANY_H
#define SPLASHCOMPANY_H

#include <QObject>
#include <QSplashScreen>
#include <QEvent>

class SplashCompany : public QSplashScreen
{
public:
    explicit SplashCompany(const QPixmap &pixmap = QPixmap(),
                           Qt::WindowFlags f = Qt::WindowFlags());
    bool eventFilter(QObject *target, QEvent *event);
};

inline SplashCompany::SplashCompany(const QPixmap &pixmap, Qt::WindowFlags f)
{
    Q_UNUSED(f)

    this->setPixmap(pixmap);
    this->installEventFilter(this);
}

inline bool SplashCompany::eventFilter(QObject *target, QEvent *event)
{
    Q_UNUSED(target)

    if((event->type() == QEvent::MouseButtonPress) ||
            (event->type() == QEvent::MouseButtonDblClick) ||
            (event->type() == QEvent::MouseButtonRelease) ||
            (event->type() == QEvent::KeyPress) ||
            (event->type() == QEvent::KeyRelease))
        return true;

    return false;
}

#endif // SPLASHCOMPANY_H
