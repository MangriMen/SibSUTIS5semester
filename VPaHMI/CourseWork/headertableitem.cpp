#include "headertableitem.h"
#include "ui_headertableitem.h"
#include "headertableitemeditpage.h"
#include <QDialog>
#include <QBoxLayout>

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

void HeaderTableItem::on_btnConfigure_clicked()
{


    QDialog* dlg = new QDialog(this);
    QVBoxLayout* layout = new QVBoxLayout(dlg);
    HeaderTableItemEditPage* page = new HeaderTableItemEditPage(dlg);

    layout->addWidget(page);
    dlg->setLayout(layout);
    dlg->setGeometry(QRect(200, 200,800, 600));
    dlg->show();
}
