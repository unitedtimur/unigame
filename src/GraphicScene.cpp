#include "include/GraphicScene.h"

void GraphicScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	Q_EMIT this->mousePressed(event);
}
