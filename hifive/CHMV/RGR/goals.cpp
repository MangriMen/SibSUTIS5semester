#include "goals.h"
#include "ui_goals.h"

Goals::Goals(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Goals)
{
    ui->setupUi(this);
}

Goals::~Goals()
{
    delete ui;
}

void Goals::on_btnTransferAccept_clicked()
{
    GoalBalanceModified();
}

void Goals::on_btnWithdrawAccept_clicked()
{
    GoalBalanceModified();
}
