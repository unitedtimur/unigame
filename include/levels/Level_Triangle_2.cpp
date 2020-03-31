#include "include/levels/Level_Triangle_2.h"
#include "include/Configuration.h"
#include "include/Matrix.h"
#include "ui_Matrix.h"
#include "include/GraphicView.h"
#include "include/GraphicScene.h"

#include <QMouseEvent>
#include <QMediaPlayer>

Level_Triangle_2::Level_Triangle_2(Matrix* matrix, GraphicView* view, GraphicScene* scene) :
	_matrix(matrix),
	_view(view),
	_scene(scene),
	_mediaPress(new QMediaPlayer)
{
	this->Level_Triangle_2::startLevel();

	connect(_view, &GraphicView::mouseClicked, [&](QMouseEvent* event)
	{
		if (_previousPos != QPoint(0, 0))
			_scene->addLine(QLineF(QPointF(_previousPos), QPointF(event->pos())), QPen(QBrush(Qt::yellow), 3));
		
		_previousPos = event->pos();
	});

	//connect(_view, &GraphicView::mouseMoved, [&](QMouseEvent* event)
	//	{
	//		_scene->addLine(QLineF(QPointF(_previousPos), QPointF(event->pos())), QPen(QBrush(Qt::yellow), 3));
	//		_previousPos = event->pos();
	//	});
	//connect(_view, &GraphicView::mouseClicked, this, &Level_Triangle_2::isInsidePolygon);
	//connect(_view, &GraphicView::mouseClicked, this, &Level_Triangle_2::playPressSound);
}

Level_Triangle_2::~Level_Triangle_2()
{
	delete _mediaPress;
}

void Level_Triangle_2::paintLevel()
{
	QVector<QPoint> points;

	qreal width = Configuration::WIDTH_VIEW / 6;
	qreal height = Configuration::HEIGHT_VIEW / 6;

	for (qint32 i = 0; i < 6; ++i)
	{
		if (i == 1)
			points.push_back(QPoint(width * i, height * 2));
		
		if (i == 2)
			points.push_back(QPoint(width * i, height * 5));

		if (i == 3)
			points.push_back(QPoint(width * i, height * 5));

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

void Level_Triangle_2::paintPoint(const QPoint& point)
{
	double rad = 5;
	_scene->addEllipse(QRectF(point.x() - rad, point.y() - rad, rad * 2.0, rad * 2.0), QPen(Qt::black, 2), QBrush(Qt::white));
}

void Level_Triangle_2::clearLevel()
{
}

void Level_Triangle_2::showTooltip()
{
	_matrix->ui->tooltip->setText(QString::fromUtf8(u8"Постройте равнобедренный\nтреугольник с вершинами в трёх из\nданных точек."));
}

void Level_Triangle_2::showHint()
{
}

void Level_Triangle_2::startLevel()
{
	// Показываем задание
	this->showTooltip();

	// Отрисовываем уровень
	this->paintLevel();
}

bool Level_Triangle_2::checkLevel(QObject* watched, QEvent* event)
{
	return true;
}

void Level_Triangle_2::finishLevel()
{
}

void Level_Triangle_2::paintPointOnGraphicView(QMouseEvent* event)
{
	double rad = 5;
	_scene->addEllipse(QRectF(event->x() - rad, event->y() - rad, rad * 2.0, rad * 2.0), QPen(), QBrush(Qt::yellow));

	_previousPos = event->pos();
}

void Level_Triangle_2::isInsidePolygon(QMouseEvent* event)
{
}

void Level_Triangle_2::playPressSound()
{
}
