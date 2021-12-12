#ifndef WIDGETBUTTON_H
#define WIDGETBUTTON_H

#include <QWidget>
#include <QMouseEvent>
#include <QFrame>

class WidgetButton : public QFrame
{
    Q_OBJECT
public:
    explicit WidgetButton(QWidget *parent = nullptr);

signals:
    void clicked();

public slots:

private:
    void mousePressEvent(QMouseEvent *event);
};

#endif // WIDGETBUTTON_H
