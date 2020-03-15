#include "include/GraphicView.h"

void GraphicView::mousePressEvent(QMouseEvent* event)
{
	emit this->mouseClicked(event);
}
