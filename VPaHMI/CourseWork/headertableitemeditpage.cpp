#include "headertableitemeditpage.h"
#include "ui_headertableitemeditpage.h"

HeaderTableItemEditPage::HeaderTableItemEditPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HeaderTableItemEditPage)
{
    ui->setupUi(this);
}

HeaderTableItemEditPage::~HeaderTableItemEditPage()
{
    delete ui;
}
