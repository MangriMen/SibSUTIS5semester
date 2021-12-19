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
    void AddToWalletAccepted(int number);
    void AddToBankAccepted(int number);
    void WithdrawFromBankAccepted(int number);
    void RecurringPaymentAccepted(int number);
    void GuiUpdated(int walletBalance, int bankBalance, int withdrawBalance, int recurringBalance);

private slots:
    void on_btnAddToBank_clicked();
    void on_btnWithdraw_clicked();
    void on_btnRecurringPayment_clicked();
    void on_btnAddToWallet_clicked();

    void onGuiUpdate(int walletBalance, int bankBalance, int withdrawBalance, int recurringBalance);

private:
    Ui::EditFunds *ui;
};

#endif // EDITFUNDS_H
