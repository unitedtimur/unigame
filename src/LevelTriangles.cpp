#include "include/LevelTriangles.h"

#include <QGraphicsScene>
#include <QPolygon>

LevelTriangles::LevelTriangles(QGraphicsScene* scene) :
	scene(scene)
{
	LevelTriangles::paintLevel();
}

LevelTriangles::~LevelTriangles()
{
	
}

void LevelTriangles::paintLevel()
{
}

void LevelTriangles::paintPoints(QPoint point)
{
	double rad = 10;
	scene->addEllipse(QRectF(point.x() - rad, point.y() - rad, rad * 2.0, rad * 2.0), QPen(), QBrush(Qt::SolidPattern));
}

void LevelTriangles::clearLevel()
{
	scene->clear();
}

void LevelTriangles::showTooltip()
{
}
