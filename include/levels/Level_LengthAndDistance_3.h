#ifndef LEVEL_LENGTH_AND_DISTANCE_3
#define LEVEL_LENGTH_AND_DISTANCE_3

#include "ILevel.h"

class QMouseEvent;
class Matrix;
class GraphicView;
class GraphicScene;

class Level_LengthAndDistance_3 final : public ILevel
{
public:
	explicit Level_LengthAndDistance_3(Matrix* matrix, GraphicView* view, GraphicScene* scene);
	~Level_LengthAndDistance_3() = default;

	Q_SLOT void paintPointOnGraphicView(QMouseEvent* event);
	Q_SLOT void isInsidePolygon(QMouseEvent* event);

protected:
	void paintLevel() override;
	void paintPoint(const QPoint& point) override;
	void clearLevel() override;
	void showTooltip() override;
	void showHint() override;
	void startLevel() override;
	bool checkLevel(QObject* watched, QEvent* event) override;
	void finishLevel() override;
	bool inArea(const QPoint& first, const QPoint& second, const qint32& epsilon = 15);

private:
	Matrix* _matrix;
	GraphicView* _view;
	GraphicScene* _scene;

	QVector<QPointF> _answersPoint;

	struct Polygon
	{
		QVector<QPoint> _points;
		QVector<bool>	_isPressed;
	} _polygon;
	
	bool _flag;
	qint32 _counter;
};

#endif // LEVEL_LENGTH_AND_DISTANCE_2