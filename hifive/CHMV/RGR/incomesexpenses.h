#ifndef INCOMESEXPENSES_H
#define INCOMESEXPENSES_H

#include <QDialog>

namespace Ui {
class IncomesExpenses;
}

class IncomesExpenses : public QDialog
{
    Q_OBJECT

public:
    explicit IncomesExpenses(QWidget *parent = 0);
    ~IncomesExpenses();

private:
    Ui::IncomesExpenses *ui;
};

#endif // INCOMESEXPENSES_H
