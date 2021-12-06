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
