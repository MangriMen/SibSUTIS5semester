#include "error.h"
#include "ui_error.h"

error::error(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::error)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags().setFlag(Qt::WindowContextHelpButtonHint, false));
}

error::~error()
{
    delete ui;
}
