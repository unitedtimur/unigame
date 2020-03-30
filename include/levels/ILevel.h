#ifndef ILEVEL_H
#define ILEVEL_H

#include <QObject>
#include <QPoint>

class ILevel : public QObject
{
	Q_OBJECT
public:
	virtual ~ILevel() = default;
	virtual void paintLevel()									= 0;
	virtual void paintPoint(const QPoint& point)				= 0;
	virtual void clearLevel()									= 0;
	virtual void showTooltip()									= 0;
	virtual void startLevel()									= 0;
	virtual bool checkLevel(QObject* watched, QEvent* event)	= 0;
	virtual void finishLevel()									= 0;
	ILevel& operator=(const ILevel&) = delete;
};

#endif // ILEVEL_H
