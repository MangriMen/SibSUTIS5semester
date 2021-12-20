#include "accountcreation.h"
#include "ui_accountcreation.h"
#include <QMessageBox>

accountCreation::accountCreation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::accountCreation)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags().setFlag(Qt::WindowContextHelpButtonHint, false));
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &accountCreation::checkAccept);
}

void accountCreation::checkAccept() {
    if (this->getName().isEmpty()) {
        QMessageBox::information(this, "Внимание", "Имя пользователя не должно быть пустым", QMessageBox::Ok);

        return;
    }

    this->accept();
}

QString accountCreation::getName() {
    return ui->lnEditAccountName->text().trimmed();
}

accountCreation::~accountCreation()
{
    delete ui;
}
