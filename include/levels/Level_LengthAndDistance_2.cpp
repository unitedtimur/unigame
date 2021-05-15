#include "include/levels/Level_LengthAndDistance_2.h"
#include "include/Matrix.h"
#include "ui_Matrix.h"
#include "include/GraphicView.h"
#include "include/GraphicScene.h"
#include "include/Configuration.h"
#include <QMouseEvent>
#include <qmath.h>
#include "include/Functions.h"

Level_LengthAndDistance_2::Level_LengthAndDistance_2(Matrix* matrix, GraphicView* view, GraphicScene* scene) :
	_matrix(matrix),
	_view(view),
	_scene(scene),
	_flag(false),
	_counter(0)
{
	this->Level_LengthAndDistance_2::startLevel();

	_matrix->ui->levelButton->setText(QObject::tr("Удалить линии и начать сначала"));

	connect(_view, &GraphicView::mouseClicked, this, &Level_LengthAndDistance_2::paintPointOnGraphicView);
	connect(_view, &GraphicView::mouseClicked, this, &Level_LengthAndDistance_2::isInsidePolygon);
}

void Level_LengthAndDistance_2::paintPointOnGraphicView(QMouseEvent* event)
{
	if (event->button() == Qt::MouseButton::LeftButton)
	{
		double rad = 5;
		_scene->addEllipse(QRectF(event->x() - rad, event->y() - rad, rad * 2.0, rad * 2.0), QPen(), QBrush(Qt::yellow));
	}
}

void Level_LengthAndDistance_2::isInsidePolygon(QMouseEvent* event)
{
	if (event->button() == Qt::MouseButton::LeftButton)
	{
		// Если пользователь нашёл середину отрезка
		if (inArea(event->pos(), _answerPoint.toPoint()))
		{
			_flag = true;
		}
	}

	// Если пользователь 10 раз не попал в нужные точки, то показываем подсказку
	if (++_counter == 10)
		this->showHint();
}

void Level_LengthAndDistance_2::paintLevel()
{
	QVector<QPoint> points;

	qreal width = Configuration::WIDTH_VIEW / 6;
	qreal height = Configuration::HEIGHT_VIEW / 6;

	for (qint32 i = 0; i < 6; ++i)
	{
		if (i == 1)
			points.push_back(QPoint(width * i, height * 4));

		if (i == 5)
			points.push_back(QPoint(width * i, height * 2));
	}

	for (const auto& point : points)
		this->paintPoint(point);

	_answerPoint = Functions::midSection(points[0], points[1]);
	_points = points;

	_scene->addLine(QLineF(QPointF(_points[0]), QPointF(_points[1])), QPen(Qt::red, 2));
}

void Level_LengthAndDistance_2::paintPoint(const QPoint& point)
{
	double rad = 5;
	_scene->addEllipse(QRectF(point.x() - rad, point.y() - rad, rad * 2.0, rad * 2.0), QPen(Qt::black, 2), QBrush(Qt::white));
}

void Level_LengthAndDistance_2::clearLevel()
{
	// Очищаем уровень
	_scene->clear();

	// Отрисовываем матрицу 
	_matrix->drawMatrix6x6();

	// Отрисовываем уровень
	this->startLevel();
}

void Level_LengthAndDistance_2::showTooltip()
{
	_matrix->ui->tooltip->setText(QObject::tr("Постройте середину отрезка."));
}

void Level_LengthAndDistance_2::showHint()
{
	_matrix->ui->hintLabel->setText(QObject::tr("Разделите отрезок мысленно пополам."));
}

void Level_LengthAndDistance_2::startLevel()
{
	// Показываем задание
	this->showTooltip();

	// Отрисовываем уровень
	this->paintLevel();
}

bool Level_LengthAndDistance_2::checkLevel(QObject* watched, QEvent* event)
{
    Q_UNUSED(watched)

	if (event->type() == QEvent::KeyPress)
	{
		QKeyEvent* keyEvent = dynamic_cast<QKeyEvent*>(event);

		if (keyEvent->key() == Qt::Key_Space)
		{
			if (!_flag)
				return false;

			// Пользователь прошёл уровень
			this->finishLevel();

			return true;
		}
	}

	return false;
}

void Level_LengthAndDistance_2::finishLevel()
{
	// Делаем красивый вывод
	this->clearLevel();

	this->paintPoint(_answerPoint.toPoint());

	_matrix->changeStatistic(QStringList() << QObject::tr("Длина и расстояние") << QObject::tr("Уровень 2") << QObject::tr("Пройден"));
}

bool Level_LengthAndDistance_2::inArea(const QPoint& first, const QPoint& second, const qint32& epsilon)
{
	return (qFabs(first.x() - second.x()) < epsilon && qFabs(first.y() - second.y()) < epsilon);
}
