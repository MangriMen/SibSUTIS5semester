#ifndef EDITFUNDS_H
#define EDITFUNDS_H

#include <QDialog>

namespace Ui {
class EditFunds;
}

class EditFunds : public QDialog
{
    Q_OBJECT

public:
    explicit EditFunds(QWidget *parent = 0);
    ~EditFunds();

private:
    Ui::EditFunds *ui;
};

#endif // EDITFUNDS_H
