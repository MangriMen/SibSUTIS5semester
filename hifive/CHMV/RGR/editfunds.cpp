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
