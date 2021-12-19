#include "editfunds.h"
#include "ui_editfunds.h"

EditFunds::EditFunds(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditFunds)
{
    ui->setupUi(this);

    connect(this, &EditFunds::GuiUpdated, this, &EditFunds::onGuiUpdate);
}

EditFunds::~EditFunds()
{
    delete ui;
}

void EditFunds::on_btnAddToWallet_clicked()
{
    AddToWalletAccepted(ui->lnEditAddToWallet->text().toInt());
}

void EditFunds::on_btnAddToBank_clicked()
{
    AddToBankAccepted(ui->lnEditAddToBank->text().toInt());
}

void EditFunds::on_btnWithdraw_clicked()
{
    WithdrawFromBankAccepted(ui->lnEditWithdraw->text().toInt());
}

void EditFunds::on_btnRecurringPayment_clicked()
{
    RecurringPaymentAccepted(ui->lnEditRecurringPayment->text().toInt());
}

void EditFunds::onGuiUpdate(int walletBalance, int bankBalance, int withdrawBalance, int recurringBalance) {
    ui->lnEditAddToBank->setPlaceholderText(QString::number(walletBalance));
    ui->lnEditAddToBank->setPlaceholderText(QString::number(bankBalance));
    ui->lnEditAddToBank->setPlaceholderText(QString::number(withdrawBalance));
    ui->lnEditAddToBank->setPlaceholderText(QString::number(recurringBalance));
}

