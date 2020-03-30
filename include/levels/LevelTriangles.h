#ifndef LEVELTRIANGLES_H
#define LEVELTRIANGLES_H

#include "include/levels/ILevel.h"
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

	static bool inArea(const QPoint& first, const QPoint& second, const qint32& epsilon = 15);

protected:
	void level_1();
	void level_1_after();


	Q_SLOT void insidePolygon(QMouseEvent* event);

public:
	bool event(QEvent* event) override;
	bool eventFilter(QObject* watched, QEvent* event) override;
private:
	Matrix*				matrix;
	GraphicScene*		scene;
	GraphicView*		view;

	enum Condition
	{
		NotInArea	= 0,
		InArea		= 1
	};

	QVector<QPoint>	polygon;


	enum Levels
	{
		No_Level	= 0,
		Level_1		= 1,
		Level_2		= 2,
		Level_3		= 3
	} levels;
};

#endif // LEVELTRIANGLES_H
