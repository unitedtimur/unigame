#include "include/GraphicScene.h"
#include <QDebug>

void GraphicScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    qDebug() << event;
	Q_EMIT this->mousePressed(event);
}
