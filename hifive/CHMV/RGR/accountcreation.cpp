#include "accountcreation.h"
#include "ui_accountcreation.h"

accountCreation::accountCreation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::accountCreation)
{
    ui->setupUi(this);
}

accountCreation::~accountCreation()
{
    delete ui;
}
