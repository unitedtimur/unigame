#ifndef LEVELTRIANGLES_H
#define LEVELTRIANGLES_H

#include "include/ILevel.h"

class QGraphicsScene;
class QPolygon;

class LevelTriangles final : public ILevel
{
public:
	explicit LevelTriangles(QGraphicsScene* scene);
	~LevelTriangles();

	void paintLevel() override;
	void paintPoints(QPoint points) override;
	void clearLevel() override;
	void showTooltip() override;

private:
	QGraphicsScene*		scene;
};

#endif // LEVELTRIANGLES_H
