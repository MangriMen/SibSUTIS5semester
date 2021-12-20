#include "editfunds.h"
#include "ui_editfunds.h"
#include <qDebug>

EditFunds::EditFunds(QSqlTableModel *model, QWidget *parent) :
    QDialog(parent),
    modelFunds(model),
    ui(new Ui::EditFunds)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags().setFlag(Qt::WindowContextHelpButtonHint, false));

    onGuiUpdate();

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
    modelFunds->select();
    modelFunds->setData(modelFunds->index(0, 2), ui->lnEditRecurringPayment->text().toInt());
    modelFunds->setData(modelFunds->index(0, 3), QDate::currentDate());
    modelFunds->submitAll();

    onGuiUpdate();
}

void EditFunds::onGuiUpdate() {
    modelFunds->select();
    QSqlQuery query = modelFunds->query();
    query.exec();

    if (query.next()) {
        ui->lnEditRecurringPayment->setText(query.value(2).value<QString>());
    }
}
