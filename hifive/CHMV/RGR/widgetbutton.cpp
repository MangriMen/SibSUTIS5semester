#include "widgetbutton.h"

WidgetButton::WidgetButton(QWidget *parent) : QFrame(parent)
{
    this->setProperty("class", "fakeButton");
    this->setCursor(QCursor(Qt::PointingHandCursor));
}

void WidgetButton::mousePressEvent(QMouseEvent *) {
    clicked();
}
