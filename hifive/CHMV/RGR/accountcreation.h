#ifndef ACCOUNTCREATION_H
#define ACCOUNTCREATION_H

#include <QDialog>

namespace Ui {
class accountCreation;
}

class accountCreation : public QDialog
{
    Q_OBJECT

public:
    explicit accountCreation(QWidget *parent = 0);
    ~accountCreation();
    QString getName();
    void checkAccept();

private:
    Ui::accountCreation *ui;
};

#endif // ACCOUNTCREATION_H
