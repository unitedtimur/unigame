#include "include/GraphicView.h"

#include <QMouseEvent>

void GraphicView::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::MouseButton::LeftButton)
	{
		Q_EMIT this->mouseClicked(event);
	}
}

void GraphicView::mouseMoveEvent(QMouseEvent* event)
{
	Q_EMIT this->mouseMoved(event);
}
