#include "include/LevelTriangles.h"
#include "ui_Matrix.h"

#include "include/GraphicScene.h"
#include "include/GraphicView.h"
#include "include/Matrix.h"

#include <QDebug>
#include <QMouseEvent>

LevelTriangles::LevelTriangles(Matrix* matrix, GraphicScene* scene, GraphicView* view) :
	matrix(matrix),
	scene(scene),
	view(view),
	polygon(new QPolygon)
{
	LevelTriangles::level_1();
	QCoreApplication::instance()->installEventFilter(this);

}

void LevelTriangles::paintLevel()
{
	delete polygon;
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

void LevelTriangles::level_1()
{
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

	polygon->append(points);

	connect(view, &GraphicView::mouseClicked, this, &LevelTriangles::insidePolygon);
}

void LevelTriangles::insidePolygon(QMouseEvent* event)
{
	if (polygon->containsPoint(QPoint(event->x(), event->y()), Qt::FillRule::OddEvenFill))
	{
		if (lines.size() == 3)
			lines.clear();

		lines.push_back(event->pos());
	}
}

bool LevelTriangles::event(QEvent* event)
{
	if (event->type() == QEvent::KeyPress)
	{
		QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

		if (keyEvent->key() == Qt::Key_Space)
		{
			for (auto i = 0; i < lines.size(); ++i)
			{
				scene->addLine(QLineF(QPointF(lines[i]), QPointF(lines[i + 1])));
			}

			return true;
		}
	}

	return false;
}

bool LevelTriangles::eventFilter(QObject* watched, QEvent* event)
{
	if (event->type() == QEvent::KeyPress)
	{
		QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

		if (keyEvent->key() == Qt::Key_Space)
		{
			for (const auto& line : lines)
			{
				//if (!polygon->contains(line))
				//{
				//	return false;
				//}

				
			}
			scene->addLine(QLineF(polygon->point(0), polygon->point(1)));
			scene->addLine(QLineF(polygon->point(1), polygon->point(2)));
			scene->addLine(QLineF(polygon->point(2), polygon->point(0)));
			return true;
		}
	}

	return false;
}
