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

signals:
    void AddToBankAccepted();
    void WithdrawFromBankAccepted();
    void RecurringPaymentAccepted();

private slots:
    void on_btnAddToBank_clicked();

    void on_btnWithdraw_clicked();

    void on_btnRecurringPayment_clicked();

private:
    Ui::EditFunds *ui;
};

#endif // EDITFUNDS_H
