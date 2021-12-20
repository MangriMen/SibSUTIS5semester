#ifndef EDITFUNDS_H
#define EDITFUNDS_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QDate>

namespace Ui {
class EditFunds;
}

class EditFunds : public QDialog
{
    Q_OBJECT

public:
    explicit EditFunds(QSqlTableModel *model, QWidget *parent = 0);
    ~EditFunds();

signals:
    void AddToWalletAccepted(int number);
    void AddToBankAccepted(int number);
    void WithdrawFromBankAccepted(int number);
    void RecurringPaymentAccepted();
    void GuiUpdated();

private slots:
    void on_btnAddToBank_clicked();
    void on_btnWithdraw_clicked();
    void on_btnRecurringPayment_clicked();
    void on_btnAddToWallet_clicked();

    void onGuiUpdate();

private:
    QSqlTableModel *modelFunds = nullptr;
    Ui::EditFunds *ui;
};

#endif // EDITFUNDS_H
