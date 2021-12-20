#include "elineedit.h"
#include <QKeyEvent>

ELineEdit::ELineEdit(QWidget* parent) :
    QLineEdit(parent)
{

}

void ELineEdit::keyPressEvent(QKeyEvent* e)
{
    QLineEdit::keyPressEvent(e);

    if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
    {
        e->accept();
    }
}
