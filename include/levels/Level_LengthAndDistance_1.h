#ifndef LEVEL_LENGTH_AND_DISTANCE_1
#define LEVEL_LENGTH_AND_DISTANCE_1

#include "ILevel.h"

class QMouseEvent;
class Matrix;
class GraphicView;
class GraphicScene;

class Level_LengthAndDistance_1 final : public ILevel
{
public:
	explicit Level_LengthAndDistance_1(Matrix* matrix, GraphicView* view, GraphicScene* scene);
	~Level_LengthAndDistance_1();

	Q_SLOT void paintPointOnGraphicView(QMouseEvent* event);
	Q_SLOT void paintLineOnGraphicView(QMouseEvent* event);
	Q_SLOT void isInsidePolygon(QMouseEvent* event);
	Q_SLOT void playPressSound();

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

	struct Polygon
	{
		QVector<QPoint> _points;
		QVector<bool>	_isPressed;
	} _polygon;

	QPoint _previousPos;

	qint32 _counter;
};

#endif // LEVEL_LENGTH_AND_DISTANCE_1
