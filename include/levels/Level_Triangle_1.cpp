#include "include/levels/Level_Triangle_1.h"

#include "include/Matrix.h"
#include "ui_Matrix.h"
#include "include/GraphicView.h"
#include "include/GraphicScene.h"

#include <QMouseEvent>
#include <QDebug>
#include <QtMath> // qFabs
			
Level_Triangle_1::Level_Triangle_1(Matrix* matrix, GraphicView* view, GraphicScene* scene) :
	_matrix(matrix),
	_view(view),
	_scene(scene)
{
	this->Level_Triangle_1::startLevel();
	//QCoreApplication::instance()->installEventFilter(this);

	connect(_view, &GraphicView::mouseClicked, this, &Level_Triangle_1::paintPointOnGraphicView);
	connect(_view, &GraphicView::mouseClicked, this, &Level_Triangle_1::isInsidePolygon);
}

void Level_Triangle_1::paintLevel()
{
	QVector<QPoint> points;

	for (qint32 i = 0; i < 6; ++i)
	{
		if (i == 1)
		{
			points.push_back(QPoint(qint32(i / 6. * _view->width()), qint32(5. * i / 6. * _view->height())));
			this->paintPoint(points[0]);
		}

		if (i == 3)
		{
			points.push_back(QPoint(qint32(i / 6. * _view->width()), 0));
			this->paintPoint(points[1]);
		}

		if (i == 5)
		{
			points.push_back(QPoint(qint32(i / 6. * _view->width()), i / 6. * _view->height()));
			this->paintPoint(points[2]);
		}
	}

	for (const auto& point : points)
	{
		_polygon._points.push_back(point);
		_polygon._isPressed.push_back(false);
	}
}

void Level_Triangle_1::paintPoint(const QPoint& point)
{
	double rad = 5;
	_scene->addEllipse(QRectF(point.x() - rad, point.y() - rad, rad * 2.0, rad * 2.0), QPen(Qt::black, 2), QBrush(Qt::white));
}

void Level_Triangle_1::clearLevel()
{
	_scene->clear();
}

void Level_Triangle_1::showTooltip()
{
	_matrix->ui->tooltip->setText(QString::fromUtf8(u8"Соедините три данные точки так,\nчтобы получился равнобедренный\nтреугольник."));
}

void Level_Triangle_1::paintPointOnGraphicView(QMouseEvent* event)
{
	qDebug() << event->pos();

	double rad = 5;
	_scene->addEllipse(QRectF(event->x() - rad, event->y() - rad, rad * 2.0, rad * 2.0), QPen(), QBrush(Qt::yellow));
}

void Level_Triangle_1::isInsidePolygon(QMouseEvent* event)
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

void Level_Triangle_1::startLevel()
{
	//QCoreApplication::instance()->installEventFilter(this);

	// Показываем задание
	this->showTooltip();

	// Отрисовываем уровень
	this->paintLevel();
}

bool Level_Triangle_1::checkLevel(QObject* watched, QEvent* event)
{
	if (event->type() == QEvent::KeyPress)
	{
		QKeyEvent* keyEvent = dynamic_cast<QKeyEvent*>(event);

		if (keyEvent->key() == Qt::Key_Space)
		{
			for (const auto& it : _polygon._isPressed)
			{
				if (it == false)
					return false;
			}

			// Пользователь прошёл уровень
			this->finishLevel();

			return true;
		}
	}
}

void Level_Triangle_1::finishLevel()
{
	_scene->addLine(QLineF(QPointF(_polygon._points[0]), QPointF(_polygon._points[1])), QPen(Qt::red, 2));
	_scene->addLine(QLineF(QPointF(_polygon._points[1]), QPointF(_polygon._points[2])), QPen(Qt::red, 2));
	_scene->addLine(QLineF(QPointF(_polygon._points[2]), QPointF(_polygon._points[0])), QPen(Qt::red, 2));
}

bool Level_Triangle_1::inArea(const QPoint& first, const QPoint& second, const qint32& epsilon)
{
	return (qFabs(first.x() - second.x()) < epsilon && qFabs(first.y() - second.y()) < epsilon);
}
