#include "editfunds.h"
#include "ui_editfunds.h"

EditFunds::EditFunds(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditFunds)
{
    ui->setupUi(this);
}

EditFunds::~EditFunds()
{
    delete ui;
}

void EditFunds::on_btnAddToBank_clicked()
{
    AddToBankAccepted();
}

void EditFunds::on_btnWithdraw_clicked()
{
    WithdrawFromBankAccepted();
}

void EditFunds::on_btnRecurringPayment_clicked()
{
    RecurringPaymentAccepted();
}
