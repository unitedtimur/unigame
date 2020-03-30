#ifndef LEVEL_TRIANGLE_1
#define LEVEL_TRIANGLE_1

#include "include/levels/ILevel.h"
#include <QPolygon>

class QMouseEvent;
class Matrix;
class GraphicView;
class GraphicScene;

class Level_Triangle_1 : public ILevel
{
	Q_OBJECT

public:
	explicit Level_Triangle_1(Matrix* matrix, GraphicView* view, GraphicScene* scene);

	void paintLevel() override;
	void paintPoint(const QPoint& point) override;
	void clearLevel() override;
	void showTooltip() override;

	Q_SLOT void paintPointOnGraphicView(QMouseEvent* event);
	Q_SLOT void isInsidePolygon(QMouseEvent* event);

protected:
	void startLevel() override;
	void showHint() override;
	bool checkLevel(QObject* watched, QEvent* event) override;
	void finishLevel() override;

	bool inArea(const QPoint& first, const QPoint& second, const qint32& epsilon = 15);

private:
	Matrix* _matrix;
	GraphicView* _view;
	GraphicScene* _scene;

	//QPolygon polygon;
	struct Polygon
	{
		QVector<QPoint> _points;
		QVector<bool>	_isPressed;
	} _polygon;
};

#endif // LEVEL_TRIANGLE_1