#ifndef GRAPHICSCENE_H
#define GRAPHICSCENE_H

#include <QGraphicsScene>

class GraphicScene : public QGraphicsScene
{
	Q_OBJECT
public:

	signals:
	void test(QGraphicsSceneMouseEvent*);
		
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // GRAPHICSCENE_H