#ifndef LEVEL_LENGTH_AND_DISTANCE_2
#define LEVEL_LENGTH_AND_DISTANCE_2

#include "ILevel.h"

class QMouseEvent;
class Matrix;
class GraphicView;
class GraphicScene;

class Level_LengthAndDistance_2 final : public ILevel
{
public:
	explicit Level_LengthAndDistance_2(Matrix* matrix, GraphicView* view, GraphicScene* scene);
	~Level_LengthAndDistance_2() = default;

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

	QPointF _answerPoint;
	QVector<QPoint> _points;
	bool _flag;
	qint32 _counter;
};

#endif // LEVEL_LENGTH_AND_DISTANCE_2