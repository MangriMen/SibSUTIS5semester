#ifndef ECOMBOBOX_H
#define ECOMBOBOX_H

#include <QComboBox>
#include <QKeyEvent>

class EComboBox : public QComboBox
{
public:
    explicit EComboBox(QWidget* parent = 0);

private:
    void keyPressEvent(QKeyEvent* e);
};

#endif // ECOMBOBOX_H
