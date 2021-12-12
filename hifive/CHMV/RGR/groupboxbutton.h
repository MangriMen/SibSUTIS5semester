#ifndef GROUPBOXBUTTON_H
#define GROUPBOXBUTTON_H

#include <QWidget>
#include <QGroupBox>
#include <QMouseEvent>

class GroupBoxButton : public QGroupBox
{
    Q_OBJECT
public:
    explicit GroupBoxButton(QWidget *parent = nullptr);

signals:
    void clicked();

public slots:

private:
    void mousePressEvent(QMouseEvent *event);
};

#endif // GROUPBOXBUTTON_H
