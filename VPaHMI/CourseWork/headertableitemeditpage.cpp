#include "headertableitemeditpage.h"
#include "ui_headertableitemeditpage.h"
#include "adddialog.h"

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

void HeaderTableItemEditPage::on_btnAdd_clicked()
{
    AddDialog* dlg = new AddDialog(this);

    dlg->show();
}
