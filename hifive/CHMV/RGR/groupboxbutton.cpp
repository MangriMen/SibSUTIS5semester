#include "groupboxbutton.h"

GroupBoxButton::GroupBoxButton(QWidget *parent) : QGroupBox(parent)
{
    this->setProperty("class", "fakeButton");
    this->setMouseTracking(true);
    this->setCursor(QCursor(Qt::PointingHandCursor));
}

void GroupBoxButton::mousePressEvent(QMouseEvent *) {
    clicked();
}
