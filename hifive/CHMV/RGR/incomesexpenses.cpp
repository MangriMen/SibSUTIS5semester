#include "incomesexpenses.h"
#include "ui_incomesexpenses.h"

IncomesExpenses::IncomesExpenses(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncomesExpenses)
{
    ui->setupUi(this);
}

IncomesExpenses::~IncomesExpenses()
{
    delete ui;
}
