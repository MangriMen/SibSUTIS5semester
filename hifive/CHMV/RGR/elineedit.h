#ifndef ELINEEDIT_H
#define ELINEEDIT_H

#include <QWidget>
#include <QLineEdit>

class ELineEdit : public QLineEdit
{
public:
    explicit ELineEdit(QWidget* parent = 0);

private:
    void keyPressEvent(QKeyEvent* e);
};

#endif // ELINEEDIT_H
