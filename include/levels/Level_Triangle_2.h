#ifndef LEVEL_TRIANGLE_2
#define LEVEL_TRIANGLE_2

#include "include/levels/ILevel.h"

class QMouseEvent;
class Matrix;
class GraphicView;
class GraphicScene;
class QMediaPlayer;

class Level_Triangle_2 final : public ILevel
{
	Q_OBJECT
public:
	explicit Level_Triangle_2(Matrix* matrix, GraphicView* view, GraphicScene* scene);
	~Level_Triangle_2();

protected:
	void paintLevel() override;
	void paintPoint(const QPoint& point) override;
	void clearLevel() override;
	void showTooltip() override;
	void showHint() override;
	void startLevel() override;
	bool checkLevel(QObject* watched, QEvent* event) override;
	bool inArea(const QPoint& first, const QPoint& second, const qint32& epsilon = 15);
	void finishLevel() override;

	Q_SLOT void paintPointOnGraphicView(QMouseEvent* event);
	Q_SLOT void paintLineOnGraphicView(QMouseEvent* event);
	Q_SLOT void isInsidePolygon(QMouseEvent* event);
	Q_SLOT void playPressSound();

private:
	Matrix* _matrix;
	GraphicView* _view;
	GraphicScene* _scene;
	QMediaPlayer* _mediaPress;

	struct Polygon
	{
		QVector<QPoint> _points;
		QVector<bool>	_isPressed;
	} _polygon;

	QPoint _previousPos;

	qint32 _counter;
};

#endif // LEVEL_TRIANGLE_2