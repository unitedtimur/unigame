#include "include/levels/Level_Triangle_1.h"
#include "include/Configuration.h"
#include "include/Matrix.h"
#include "ui_Matrix.h"
#include "include/GraphicView.h"
#include "include/GraphicScene.h"

#include <QMouseEvent>
#include <QtMath> // qFabs
#include <QMediaPlayer>

Level_Triangle_1::Level_Triangle_1(Matrix* matrix, GraphicView* view, GraphicScene* scene) :
	_matrix(matrix),
	_view(view),
	_scene(scene),
	_mediaPress(new QMediaPlayer),
	_counter(0)
{
	this->Level_Triangle_1::startLevel();

	_mediaPress->setMedia(QUrl(Configuration::AUDIO_PRESS_MOUSE_LEFT));
	_mediaPress->setPlaybackRate(3);

	connect(_view, &GraphicView::mouseClicked, this, &Level_Triangle_1::paintPointOnGraphicView);
	connect(_view, &GraphicView::mouseClicked, this, &Level_Triangle_1::isInsidePolygon);
	connect(_view, &GraphicView::mouseClicked, this, &Level_Triangle_1::playPressSound);
}

Level_Triangle_1::~Level_Triangle_1()
{
	delete _mediaPress;
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
	_matrix->ui->tooltip->setText(QObject::tr("Соедините три данные точки так,\nчтобы получился равнобедренный\nтреугольник."));
}

void Level_Triangle_1::paintPointOnGraphicView(QMouseEvent* event)
{
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

	// Если пользователь 10 раз не попал в нужные точки, то показываем подсказку
	if (++_counter == 10)
		this->showHint();
}

void Level_Triangle_1::playPressSound()
{
	_mediaPress->play();
}

void Level_Triangle_1::startLevel()
{
	// Показываем задание
	this->showTooltip();

	// Отрисовываем уровень
	this->paintLevel();
}

void Level_Triangle_1::showHint()
{
	_matrix->ui->hintLabel->setText(QObject::tr("Подсказка\nЧтобы решить уровень достаточно единожды попасть в каждую из точек!"));
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

void Level_Triangle_1::finishLevel()
{
	_scene->addLine(QLineF(QPointF(_polygon._points[0]), QPointF(_polygon._points[1])), QPen(Qt::red, 2));
	_scene->addLine(QLineF(QPointF(_polygon._points[1]), QPointF(_polygon._points[2])), QPen(Qt::red, 2));
	_scene->addLine(QLineF(QPointF(_polygon._points[2]), QPointF(_polygon._points[0])), QPen(Qt::red, 2));

	_matrix->changeStatistic(QStringList() << QObject::tr("Равнобедренные треугольники") << QObject::tr("Уровень 1") << QObject::tr("Пройден"));
}

bool Level_Triangle_1::inArea(const QPoint& first, const QPoint& second, const qint32& epsilon)
{
	return (qFabs(first.x() - second.x()) < epsilon && qFabs(first.y() - second.y()) < epsilon);
}
