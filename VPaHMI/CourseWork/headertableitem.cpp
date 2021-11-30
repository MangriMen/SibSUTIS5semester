#include "headertableitem.h"
#include "ui_headertableitem.h"

HeaderTableItem::HeaderTableItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HeaderTableItem)
{
    ui->setupUi(this);
}

HeaderTableItem::~HeaderTableItem()
{
    delete ui;
}
