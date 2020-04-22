#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QPoint>
#include <qmath.h>

namespace Functions
{
	inline bool inArea(const QPoint& first, const QPoint& second, const qint32& epsilon = 15)
	{
		return (qFabs(first.x() - second.x()) < epsilon && qFabs(first.y() - second.y()) < epsilon);
	}

	inline qreal lengthBetweenPoints(const QPoint& first, const QPoint& second)
	{
		return qPow(qPow(first.x() - second.x(), 2) + qPow(first.y() - second.y(), 2), 0.5);
	}

	inline QPointF midSection(const QPoint& first, const QPoint& second)
	{
		return QPointF((first.x() + second.x()) / 2, (first.y() + second.y()) / 2);
	}
}

#endif // FUNCTIONS_H
