#ifndef LEVELTRIANGLES_H
#define LEVELTRIANGLES_H

#include "include/ILevel.h"
#include <QVector>

class QGraphicsScene;
class QGraphicsView;

class LevelTriangles final : public ILevel
{
public:
	explicit LevelTriangles(QGraphicsScene* scene, QGraphicsView* view);
	~LevelTriangles() = default;

	void paintLevel() override;
	void paintPoint(const QPoint& point) override;
	void clearLevel() override;
	void showTooltip() override;

protected:
	void level_1();

	
private:
	QGraphicsScene*		scene;
	QGraphicsView*		view;
	QVector<QPoint>		points;
};

#endif // LEVELTRIANGLES_H
