#ifndef LEVELTRIANGLES_H
#define LEVELTRIANGLES_H

#include "include/ILevel.h"

class QPolygon;

class LevelTriangles : public ILevel
{
public:
	explicit LevelTriangles(QPolygon* polygon);
	~LevelTriangles();

	void paintLevel() override;
	void clearLevel() override;
	void showTooltip() override;

private:
	QPolygon* polygon;
};

#endif // LEVELTRIANGLES_H
