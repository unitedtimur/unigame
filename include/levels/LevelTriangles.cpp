#include "include/levels/LevelTriangles.h"
#include "ui_Matrix.h"

#include "include/GraphicScene.h"
#include "include/GraphicView.h"
#include "include/Matrix.h"

#include <QDebug>
#include <QMouseEvent>
#include <QtMath> // qFabs

LevelTriangles::LevelTriangles(Matrix* matrix, GraphicScene* scene, GraphicView* view) :
	matrix(matrix),
	scene(scene),
	view(view),
	//polygon(new QPolygon),
	levels(Levels::No_Level)
{
	LevelTriangles::level_1();
	QCoreApplication::instance()->installEventFilter(this);

}

void LevelTriangles::paintLevel()
{
	//delete polygon;
}

void LevelTriangles::paintPoint(const QPoint& point)
{
	double rad = 5;
	scene->addEllipse(QRectF(point.x() - rad, point.y() - rad, rad * 2.0, rad * 2.0), QPen(Qt::black, 2), QBrush(Qt::white));
}

void LevelTriangles::clearLevel()
{
	scene->clear();
}

void LevelTriangles::showTooltip()
{
}

bool LevelTriangles::inArea(const QPoint& first, const QPoint& second, const qint32& epsilon)
{
	return (qFabs(first.x() - second.x()) < epsilon && qFabs(first.y() - second.y()) < epsilon);
}

void LevelTriangles::level_1()
{
	levels = Levels::Level_1;

	matrix->ui->tooltip->setText(QString::fromUtf8(u8"Соедините три данные точки так,\nчтобы получился равнобедренный\nтреугольник."));

	QVector<QPoint> points;

	for (qint32 i = 0; i < 6; ++i)
	{
		if (i == 1)
		{
			points.push_back(QPoint(qint32(i / 6. * view->width()), qint32(5. * i / 6. * view->height())));
			this->paintPoint(points[0]);
		}

		if (i == 3)
		{
			points.push_back(QPoint(qint32(i / 6. * view->width()), 0));
			this->paintPoint(points[1]);
		}

		if (i == 5)
		{
			points.push_back(QPoint(qint32(i / 6. * view->width()), i / 6. * view->height()));
			this->paintPoint(points[2]);
		}
	}

	for (const auto& point : points)
	{
		polygon.push_back(point);
	}

	connect(view, &GraphicView::mouseClicked, this, &LevelTriangles::insidePolygon);
}

void LevelTriangles::level_1_after()
{
	disconnect(view, &GraphicView::mouseClicked, this, &LevelTriangles::insidePolygon);

	//auto iterator = polygon.begin();
	//
	//scene->addLine(QLineF(QPointF(iterator), (iterator + 1)), QPen(Qt::red, 1));
	//scene->addLine(QLineF((iterator + 1).key(), (iterator + 2).key()), QPen(Qt::red, 1));
	//scene->addLine(QLineF((iterator + 2).key(), iterator.key()), QPen(Qt::red, 1));


	scene->addLine(QLineF(QPointF(polygon[0]), QPointF(polygon[1])), QPen(Qt::red, 2));
	scene->addLine(QLineF(QPointF(polygon[1]), QPointF(polygon[2])), QPen(Qt::red, 2));
	scene->addLine(QLineF(QPointF(polygon[2]), QPointF(polygon[0])), QPen(Qt::red, 2));

	levels = Levels::No_Level;
}

void LevelTriangles::insidePolygon(QMouseEvent* event)
{
	for (auto it = polygon.begin(); it != polygon.end(); ++it)
	{
		//if (LevelTriangles::inArea(event->pos(), it.key()) && it.value() != Condition::InArea)
		//{
		//	//it.value() = Condition::InArea;
		//}
	}
}

bool LevelTriangles::event(QEvent* event)
{

	return false;
}

bool LevelTriangles::eventFilter(QObject* watched, QEvent* event)
{
	if (event->type() == QEvent::KeyPress)
	{
		QKeyEvent* keyEvent = dynamic_cast<QKeyEvent*>(event);

		if (keyEvent->key() == Qt::Key_Space)
		{
			switch (levels)
			{
			case Levels::Level_1:
				this->level_1_after();
				return true;

			default:
				levels = Levels::No_Level;
			}
		}
	}

	return false;
}
