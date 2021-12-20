#include "ecombobox.h"

EComboBox::EComboBox(QWidget* parent):
    QComboBox(parent)
{

}

void EComboBox::keyPressEvent(QKeyEvent* e)
{
    QComboBox::keyPressEvent(e);

    if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
    {
        e->accept();
    }
}
