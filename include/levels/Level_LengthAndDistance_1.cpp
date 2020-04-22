#include "include/levels/Level_LengthAndDistance_1.h"
#include "include/Matrix.h"
#include "ui_Matrix.h"
#include "include/GraphicView.h"
#include "include/GraphicScene.h"
#include "include/Configuration.h"
#include <QMouseEvent>
#include <qmath.h>

Level_LengthAndDistance_1::Level_LengthAndDistance_1(Matrix* matrix, GraphicView* view, GraphicScene* scene) :
	_matrix(matrix),
	_view(view),
	_scene(scene)
{
	this->Level_LengthAndDistance_1::startLevel();

	_matrix->ui->levelButton->setText(QString::fromUtf8(u8"Удалить линии и начать сначала"));

	connect(_view, &GraphicView::mouseClicked, this, &Level_LengthAndDistance_1::paintLineOnGraphicView);
	connect(_view, &GraphicView::mouseClicked, this, &Level_LengthAndDistance_1::isInsidePolygon);
	connect(_matrix->ui->levelButton, &QPushButton::clicked, this, &Level_LengthAndDistance_1::clearLevel);
}

Level_LengthAndDistance_1::~Level_LengthAndDistance_1()
{
}

void Level_LengthAndDistance_1::paintPointOnGraphicView(QMouseEvent* event)
{
	double rad = 5;
	_scene->addEllipse(QRectF(event->x() - rad, event->y() - rad, rad * 2.0, rad * 2.0), QPen(), QBrush(Qt::yellow));

	_previousPos = event->pos();
}

void Level_LengthAndDistance_1::paintLineOnGraphicView(QMouseEvent* event)
{
	if (event->button() == Qt::MouseButton::RightButton)
	{
		if (_previousPos != QPoint())
			_scene->addLine(QLineF(QPointF(_previousPos), QPointF(event->pos())), QPen(QBrush(Qt::yellow), 3));

		_previousPos = event->pos();
	}
}

void Level_LengthAndDistance_1::isInsidePolygon(QMouseEvent* event)
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

	// Если пользователь 10 раз не попал в нужные точки, то показываем подсказку
	if (++_counter == 10)
		_matrix->ui->hintLabel->setText(_matrix->ui->hintLabel->text() + QString::fromUtf8(u8"\nПопробуйте начать с крайней левой верхней точки"));
}

void Level_LengthAndDistance_1::playPressSound()
{
}

void Level_LengthAndDistance_1::paintLevel()
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
	{
		this->paintPoint(point);
		_polygon._points.push_back(point);
		_polygon._isPressed.push_back(false);
	}
}

void Level_LengthAndDistance_1::paintPoint(const QPoint& point)
{
	double rad = 5;
	_scene->addEllipse(QRectF(point.x() - rad, point.y() - rad, rad * 2.0, rad * 2.0), QPen(Qt::black, 2), QBrush(Qt::white));
}

void Level_LengthAndDistance_1::clearLevel()
{
	// Очищаем уровень
	_previousPos = QPoint();
	_scene->clear();

	// Отрисовываем матрицу 
	_matrix->drawMatrix6x6();

	// Отрисовываем уровень
	this->startLevel();
}

void Level_LengthAndDistance_1::showTooltip()
{
	_matrix->ui->tooltip->setText(QString::fromUtf8(u8"Постройте отрезок, соединяющий две\nданные точки."));
}

void Level_LengthAndDistance_1::showHint()
{
	_matrix->ui->hintLabel->setText(QString::fromUtf8(u8"Соединяйте линии правой кнопкой мыши.\nВнимание! Выберите правильное начало нажатий!"));
}

void Level_LengthAndDistance_1::startLevel()
{
	// Сразу показываем подсказку / инструкцию к уровню
	this->showHint();

	// Показываем задание
	this->showTooltip();

	// Отрисовываем уровень
	this->paintLevel();
}

bool Level_LengthAndDistance_1::checkLevel(QObject* watched, QEvent* event)
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
}

void Level_LengthAndDistance_1::finishLevel()
{
	// Делаем красивый вывод
	this->clearLevel();

	_scene->addLine(QLineF(QPointF(_polygon._points[0]), QPointF(_polygon._points[1])), QPen(Qt::red, 2));
	_scene->addLine(QLineF(QPointF(_polygon._points[1]), QPointF(_polygon._points[2])), QPen(Qt::red, 2));

	_matrix->changeStatistic(QStringList() << QString::fromUtf8(u8"Длина и расстояние") << QString::fromUtf8(u8"Уровень 1") << QString::fromUtf8(u8"Пройден"));
}

bool Level_LengthAndDistance_1::inArea(const QPoint& first, const QPoint& second, const qint32& epsilon)
{
	return (qFabs(first.x() - second.x()) < epsilon && qFabs(first.y() - second.y()) < epsilon);
}
