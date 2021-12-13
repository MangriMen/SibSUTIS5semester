#include "accountcreation.h"
#include "ui_accountcreation.h"

accountCreation::accountCreation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::accountCreation)
{
    ui->setupUi(this);
}

QString accountCreation::getName() {
    return ui->lnEditAccountName->text().trimmed();
}

accountCreation::~accountCreation()
{
    delete ui;
}
