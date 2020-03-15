#include "include/LevelTriangles.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPolygon>
#include <QDebug>

LevelTriangles::LevelTriangles(QGraphicsScene* scene, QGraphicsView* view) :
	scene(scene),
	view(view)
{
	LevelTriangles::level_1();
}

void LevelTriangles::paintLevel()
{
}

void LevelTriangles::paintPoint(const QPoint& point)
{
	double rad = 10;
	scene->addEllipse(QRectF(point.x() - rad, point.y() - rad, rad * 2.0, rad * 2.0), QPen(), QBrush(Qt::white));
}

void LevelTriangles::clearLevel()
{
	scene->clear();
}

void LevelTriangles::showTooltip()
{
}

void LevelTriangles::level_1()
{
	for (qint32 i = 0; i < 6; ++i)
	{
		if (i == 1)
		{
			this->paintPoint(QPoint(qint32(i / 6. * view->width()), qint32(5. * i / 6. * view->height())));
		}

		if (i == 3)
		{
			this->paintPoint(QPoint(qint32(i / 6. * view->width()), 0));
		}

		if (i == 5)
		{
			this->paintPoint(QPoint(qint32(i / 6. * view->width()), i / 6. * view->height()));
		}
	}
}
