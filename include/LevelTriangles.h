#ifndef LEVELTRIANGLES_H
#define LEVELTRIANGLES_H

#include "include/ILevel.h"
#include <QObject>
#include <QPolygon>
#include <QMap>

class QMouseEvent;
class Matrix;
class GraphicScene;
class GraphicView;

class LevelTriangles final : public ILevel
{
	Q_OBJECT
public:
	explicit LevelTriangles(Matrix* matrix, GraphicScene* scene, GraphicView* view);
	~LevelTriangles() = default;

	void paintLevel() override;
	void paintPoint(const QPoint& point) override;
	void clearLevel() override;
	void showTooltip() override;

protected:
	void level_1();

	Q_SLOT void insidePolygon(QMouseEvent* event);

public:
	bool event(QEvent* event) override;
	bool eventFilter(QObject* watched, QEvent* event) override;
private:
	Matrix*				matrix;
	GraphicScene*		scene;
	GraphicView*		view;
	QVector<QPoint>		points;
	QPolygon*			polygon;

	QVector<QPoint>		lines;
};

#endif // LEVELTRIANGLES_H
