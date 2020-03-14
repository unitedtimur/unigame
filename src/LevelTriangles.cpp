#include "include/LevelTriangles.h"

#include <QPolygon>

LevelTriangles::LevelTriangles(QPolygon* polygon) :
	polygon(polygon)
{
}

LevelTriangles::~LevelTriangles()
{
	delete polygon;
}

void LevelTriangles::paintLevel()
{
}

void LevelTriangles::clearLevel()
{
}

void LevelTriangles::showTooltip()
{
}
