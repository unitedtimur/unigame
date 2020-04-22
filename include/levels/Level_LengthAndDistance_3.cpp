#include "include/levels/Level_LengthAndDistance_3.h"
#include "include/Matrix.h"
#include "ui_Matrix.h"
#include "include/GraphicView.h"
#include "include/GraphicScene.h"
#include "include/Configuration.h"
#include <QMouseEvent>
#include <qmath.h>
#include "include/Functions.h"

Level_LengthAndDistance_3::Level_LengthAndDistance_3(Matrix* matrix, GraphicView* view, GraphicScene* scene) :
	_matrix(matrix),
	_view(view),
	_scene(scene),
	_flag(false),
	_counter(0)
{
	this->Level_LengthAndDistance_3::startLevel();

	_matrix->ui->levelButton->setText(QString::fromUtf8(u8"Удалить линии и начать сначала"));

	connect(_view, &GraphicView::mouseClicked, this, &Level_LengthAndDistance_3::paintPointOnGraphicView);
	connect(_view, &GraphicView::mouseClicked, this, &Level_LengthAndDistance_3::isInsidePolygon);
}

void Level_LengthAndDistance_3::paintPointOnGraphicView(QMouseEvent* event)
{
	if (event->button() == Qt::MouseButton::LeftButton)
	{
		double rad = 5;
		_scene->addEllipse(QRectF(event->x() - rad, event->y() - rad, rad * 2.0, rad * 2.0), QPen(), QBrush(Qt::yellow));
	}
}

void Level_LengthAndDistance_3::isInsidePolygon(QMouseEvent* event)
{
	if (event->button() == Qt::MouseButton::LeftButton)
	{
		for (qint32 i = 0; i < _answersPoint.size(); ++i)
		{
			if (inArea(_answersPoint[i].toPoint(), event->pos()))
			{
				// Если пользователь попал в область указанных точек, то выставляем флаг попадания на true
				_polygon._isPressed[i] = true;
			}
		}
	}

	// Если пользователь 10 раз не попал в нужные точки, то показываем подсказку
	if (++_counter == 10)
		this->showHint();
}

void Level_LengthAndDistance_3::paintLevel()
{
	QVector<QPoint> points;

	qreal width = Configuration::WIDTH_VIEW / 6;
	qreal height = Configuration::HEIGHT_VIEW / 6;

	for (qint32 i = 0; i < 6; ++i)
	{
		if (i == 2)
			points.push_back(QPoint(width * i, height * 6));

		if (i == 3)
			_answersPoint.push_back(QPointF(width * i, height * 4));

		if (i == 4)
			_answersPoint.push_back(QPointF(width * i, height * 2));

		if (i == 5)
			points.push_back(QPoint(width * i, 0));
	}

	for (const auto& point : points)
	{
		this->paintPoint(point);
		_polygon._points.push_back(point);
		_polygon._isPressed.push_back(false);
	}

	_scene->addLine(QLineF(QPointF(_polygon._points[0]), QPointF(_polygon._points[1])), QPen(Qt::red, 2));
}

void Level_LengthAndDistance_3::paintPoint(const QPoint& point)
{
	double rad = 5;
	_scene->addEllipse(QRectF(point.x() - rad, point.y() - rad, rad * 2.0, rad * 2.0), QPen(Qt::black, 2), QBrush(Qt::white));
}

void Level_LengthAndDistance_3::clearLevel()
{
	// Очищаем уровень
	_scene->clear();

	// Отрисовываем матрицу 
	_matrix->drawMatrix6x6();

	// Отрисовываем уровень
	this->startLevel();
}

void Level_LengthAndDistance_3::showTooltip()
{
	_matrix->ui->tooltip->setText(QString::fromUtf8(u8"Постройте две точки, делящие\nотрезок на три равные части."));
}

void Level_LengthAndDistance_3::showHint()
{
	_matrix->ui->hintLabel->setText(QString::fromUtf8(u8"Попробуйте воспользоваться теоремой Пифагора."));
}

void Level_LengthAndDistance_3::startLevel()
{
	// Показываем задание
	this->showTooltip();

	// Отрисовываем уровень
	this->paintLevel();
}

bool Level_LengthAndDistance_3::checkLevel(QObject* watched, QEvent* event)
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

void Level_LengthAndDistance_3::finishLevel()
{
	// Делаем красивый вывод
	this->clearLevel();

	this->paintPoint(_answersPoint[0].toPoint());
	this->paintPoint(_answersPoint[1].toPoint());

	_matrix->changeStatistic(QStringList() << QString::fromUtf8(u8"Длина и расстояние") << QString::fromUtf8(u8"Уровень 3") << QString::fromUtf8(u8"Пройден"));
}

bool Level_LengthAndDistance_3::inArea(const QPoint& first, const QPoint& second, const qint32& epsilon)
{
	return (qFabs(first.x() - second.x()) < epsilon && qFabs(first.y() - second.y()) < epsilon);
}
