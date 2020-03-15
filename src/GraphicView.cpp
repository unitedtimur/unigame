#include "include/GraphicView.h"

#include <QMouseEvent>

void GraphicView::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::MouseButton::LeftButton)
	{
		emit this->mouseClicked(event);
	}
}

void GraphicView::mouseMoveEvent(QMouseEvent* event)
{
	//if (event->button() == Qt::MouseButton::LeftButton)
	//{
	//	emit this->mouseClicked(event);
	//}
}