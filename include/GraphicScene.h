#ifndef GRAPHICSCENE_H
#define GRAPHICSCENE_H

#include <QGraphicsScene>

class GraphicScene : public QGraphicsScene
{
	Q_OBJECT

public:

	Q_SIGNAL void mousePressed(QGraphicsSceneMouseEvent*);
		
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // GRAPHICSCENE_H