#ifndef GRAPHICVIEW_H
#define GRAPHICVIEW_H

#include <QGraphicsView>

class GraphicView : public QGraphicsView
{
	Q_OBJECT

public:
	Q_SIGNAL void mouseClicked(QMouseEvent* event);

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
};

#endif // GRAPHICVIEW_H