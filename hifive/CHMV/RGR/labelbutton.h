#ifndef LABELBUTTON_H
#define LABELBUTTON_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

class LabelButton : public QLabel
{
    Q_OBJECT
public:
    explicit LabelButton(QWidget* parent = nullptr);

signals:
    void clicked();

private:
    void mousePressEvent(QMouseEvent* event);
};

#endif // LABELBUTTON_H
