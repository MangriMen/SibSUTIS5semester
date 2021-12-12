#include "widgetbutton.h"
#include <QListView>

WidgetButton::WidgetButton(QWidget *parent) : QFrame(parent)
{
    this->setProperty("class", "fakeButton");
    this->setCursor(QCursor(Qt::PointingHandCursor));
    foreach (QListView* list, this->findChildren<QListView*>()) {
        list->setCursor(QCursor(Qt::ArrowCursor));
    }
}

void WidgetButton::mousePressEvent(QMouseEvent *) {
    clicked();
}
