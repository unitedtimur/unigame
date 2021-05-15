#include "include/levels/Level_Parallelogram_2.h"
#include "include/Matrix.h"
#include "ui_Matrix.h"
#include "include/GraphicView.h"
#include "include/GraphicScene.h"
#include "include/Configuration.h"
#include <QMouseEvent>
#include <qmath.h>

Level_Parallelogram_2::Level_Parallelogram_2(Matrix* matrix, GraphicView* view, GraphicScene* scene) :
    _matrix(matrix),
    _view(view),
    _scene(scene)
{
    this->Level_Parallelogram_2::startLevel();

    _matrix->ui->levelButton->setText(QObject::tr("Удалить линии и начать сначала"));

    connect(_view, &GraphicView::mouseClicked, this, &Level_Parallelogram_2::paintLineOnGraphicView);
    connect(_view, &GraphicView::mouseClicked, this, &Level_Parallelogram_2::isInsidePolygon);
    connect(_matrix->ui->levelButton, &QPushButton::clicked, this, &Level_Parallelogram_2::clearLevel);
}

void Level_Parallelogram_2::paintPointOnGraphicView(QMouseEvent* event)
{
    double rad = 5;
    _scene->addEllipse(QRectF(event->x() - rad, event->y() - rad, rad * 2.0, rad * 2.0), QPen(), QBrush(Qt::yellow));

    _previousPos = event->pos();
}

void Level_Parallelogram_2::paintLineOnGraphicView(QMouseEvent* event)
{
    if (event->button() == Qt::MouseButton::RightButton)
    {
        if (_previousPos != QPoint())
            _scene->addLine(QLineF(QPointF(_previousPos), QPointF(event->pos())), QPen(QBrush(Qt::yellow), 4));

        _previousPos = event->pos();
    }
}

void Level_Parallelogram_2::isInsidePolygon(QMouseEvent* event)
{
    if (event->button() == Qt::MouseButton::RightButton)
    {
        for (qint32 i = 0; i < _polygon._points.size(); ++i)
        {
            if (inArea(_polygon._points[i], event->pos()))
            {
                // Если пользователь попал в область указанных точек, то выставляем флаг попадания на true
                _polygon._isPressed[i] = true;
            }
        }
    }
}

void Level_Parallelogram_2::playPressSound()
{
}

void Level_Parallelogram_2::paintLevel()
{
    QVector<QPoint> points;

    qreal width = Configuration::WIDTH_VIEW / 6;
    qreal height = Configuration::HEIGHT_VIEW / 6;

    for (qint32 i = 0; i < 6; ++i)
    {
        if (i == 1)
            points.push_back(QPoint(width * 5, height * 1));

        if (i == 2)
            points.push_back(QPoint(width * 1, height * 2));

        if (i == 4)
            points.push_back(QPoint(width * 6, height * 4));

        if (i == 5)
            points.push_back(QPoint(width * 2, height * 5));
    }

    qint32 i = 0;

    for (const auto& point : points)
    {
        if (i != 2)
            this->paintPoint(point);

        _polygon._points.push_back(point);
        _polygon._isPressed.push_back(false);

        ++i;
    }
}

void Level_Parallelogram_2::paintPoint(const QPoint& point)
{
    double rad = 5;
    _scene->addEllipse(QRectF(point.x() - rad, point.y() - rad, rad * 2.0, rad * 2.0),
                       QPen(Qt::black, 2), QBrush(Qt::white));
}

void Level_Parallelogram_2::clearLevel()
{
    // Очищаем уровень
    _previousPos = QPoint();
    _scene->clear();

    // Отрисовываем матрицу
    _matrix->drawMatrix6x6();

    // Отрисовываем уровень
    this->startLevel();
}

void Level_Parallelogram_2::showTooltip()
{
}

void Level_Parallelogram_2::showHint()
{
    _matrix->ui->hintLabel->setText(QObject::tr("Постройте параллелограмм, для\nкоторого три данные точки являются\nвершинами."));
}

void Level_Parallelogram_2::startLevel()
{
    // Сразу показываем подсказку / инструкцию к уровню
    this->showHint();

    // Показываем задание
    this->showTooltip();

    // Отрисовываем уровень
    this->paintLevel();
}

bool Level_Parallelogram_2::checkLevel(QObject* watched, QEvent* event)
{
    Q_UNUSED(watched)

    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent = dynamic_cast<QKeyEvent*>(event);

        if (keyEvent->key() == Qt::Key_Space)
        {
            for (const auto& it : _polygon._isPressed)
            {
                if (!it)
                    return false;
            }

            // Пользователь прошёл уровень
            this->finishLevel();

            return true;
        }
    }

    return false;
}

void Level_Parallelogram_2::finishLevel()
{
    // Делаем красивый вывод
    this->clearLevel();

    _scene->addLine(QLineF(QPointF(_polygon._points[0]), QPointF(_polygon._points[1])), QPen(Qt::red, 2));
    _scene->addLine(QLineF(QPointF(_polygon._points[1]), QPointF(_polygon._points[3])), QPen(Qt::red, 2));
    _scene->addLine(QLineF(QPointF(_polygon._points[3]), QPointF(_polygon._points[2])), QPen(Qt::red, 2));
    _scene->addLine(QLineF(QPointF(_polygon._points[2]), QPointF(_polygon._points[0])), QPen(Qt::red, 2));

    _matrix->changeStatistic(QStringList() << QObject::tr("Параллелограммы")
                             << QObject::tr("Уровень 2")
                             << QObject::tr("Пройден"));
}

bool Level_Parallelogram_2::inArea(const QPoint& first, const QPoint& second, const qint32& epsilon)
{
    return (qFabs(first.x() - second.x()) < epsilon && qFabs(first.y() - second.y()) < epsilon);
}
