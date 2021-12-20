#include "incomesexpenses.h"
#include "ui_incomesexpenses.h"
#include "ecombobox.h"
#include <QSqlQuery>
#include <QDebug>
#include <QString>

IncomesExpenses::IncomesExpenses(QSqlTableModel *tableModel, QString title, QWidget *parent) :
    QDialog(parent),
    incomesExpensesModel(tableModel),
    windowTitle(title),
    ui(new Ui::IncomesExpenses)
{
    ui->setupUi(this);
    this->setWindowTitle(windowTitle);
    this->setWindowFlags(this->windowFlags().setFlag(Qt::WindowContextHelpButtonHint, false));

    ui->lnEditAddEdit->setValidator(new QIntValidator(0, 9999999, this));
    ui->lnEditRecurringPayment->setValidator(new QIntValidator(0, 9999999, this));

    onGuiUpdate();

    connect(ui->cmbAddIncomesexpences, SIGNAL(currentIndexChanged(QString)), this, SLOT(onAddEditCmbChanged(QString)));
    connect(ui->lnEditAddEdit, &QLineEdit::textChanged, this, &IncomesExpenses::onAddIncomesexpencesChanged);
    connect(ui->cmbRecurringIncomesexpences, SIGNAL(currentIndexChanged(QString)), this, SLOT(onRecurringCmbChanged(QString)));
    connect(ui->lnEditRecurringPayment, &QLineEdit::textChanged, this, &IncomesExpenses::onRecurringChanged);
    connect(ui->btnDeleteAddEdit, &QPushButton::clicked, this, &IncomesExpenses::onItemRemove);
}

void IncomesExpenses::onGuiUpdate() {
    incomesExpensesModel->select();
    QSqlQuery query = incomesExpensesModel->query();
    query.exec();

    QString cmbAddIncomesexpencesSelected = ui->cmbAddIncomesexpences->currentText();
    QString cmbRecurringIncomesexpencesSelected = ui->cmbRecurringIncomesexpences->currentText();

    ui->cmbAddIncomesexpences->clear();
    ui->cmbAddIncomesexpences->addItem("Выберете вариант");
    ui->cmbAddIncomesexpences->insertSeparator(1);

    ui->cmbRecurringIncomesexpences->clear();
    ui->cmbRecurringIncomesexpences->addItem("Выберете вариант");
    ui->cmbRecurringIncomesexpences->insertSeparator(1);

    int childrenCount = 0;
    while (query.next())
    {
        QString item = query.value(0).value<QString>();
        ui->cmbAddIncomesexpences->addItem(item);
        ui->cmbRecurringIncomesexpences->addItem(item);

        childrenCount++;
    }

    ui->cmbAddIncomesexpences->insertSeparator(childrenCount + 2);
    ui->cmbAddIncomesexpences->addItem("Добавить");

    if (!cmbAddIncomesexpencesSelected.isEmpty()) {
        ui->cmbAddIncomesexpences->setCurrentText(cmbAddIncomesexpencesSelected);
    }
    if (!cmbRecurringIncomesexpencesSelected.isEmpty()) {
        ui->cmbRecurringIncomesexpences->setCurrentText(cmbRecurringIncomesexpencesSelected);
    }

    ui->cmbAddIncomesexpences->currentTextChanged(ui->cmbAddIncomesexpences->currentText());
}

void IncomesExpenses::onAddEditCmbChanged(QString item) {
    if (item == "Выберете вариант" || item == "") {
        ui->cmbAddIncomesexpences->setEditable(false);
        ui->lnEditAddEdit->clear();
        return;
    }
    ui->cmbAddIncomesexpences->setEditable(true);
    ui->cmbAddIncomesexpences->lineEdit()->setFont(ui->cmbAddIncomesexpences->font());

    if (item == "Добавить") {
        ui->cmbAddIncomesexpences->lineEdit()->clear();
        ui->lnEditAddEdit->clear();
        return;
    }

    QSqlQuery query = incomesExpensesModel->query();
    query.prepare("SELECT * FROM "
                  + incomesExpensesModel->tableName()
                  + " WHERE "
                  + incomesExpensesModel->tableName().remove(incomesExpensesModel->tableName().size() - 1, 1)
                  + " = '"
                  + item
                  + "'");
    query.exec();

    if (query.first()) {
        ui->lnEditAddEdit->setText(query.value(1).value<QString>());
    } else {
        int newRowIndex = incomesExpensesModel->rowCount();
        incomesExpensesModel->insertRow(newRowIndex);
        incomesExpensesModel->setData(incomesExpensesModel->index(newRowIndex, 0), item);
        incomesExpensesModel->setData(incomesExpensesModel->index(newRowIndex, 1), 0); // value
        incomesExpensesModel->setData(incomesExpensesModel->index(newRowIndex, 2), 0); // recurring
        incomesExpensesModel->setData(incomesExpensesModel->index(newRowIndex, 3), "1970-01-01");
        incomesExpensesModel->submitAll();

        onGuiUpdate();
    }
}

void IncomesExpenses::onRecurringCmbChanged(QString item) {
    if (item == "Выберете вариант" || item == "") {
        ui->lnEditRecurringPayment->setText(QString::number(0));
        return;
    }

    QSqlQuery query = incomesExpensesModel->query();
    query.prepare("SELECT * FROM "
                  + incomesExpensesModel->tableName()
                  + " WHERE "
                  + incomesExpensesModel->tableName().remove(incomesExpensesModel->tableName().size() - 1, 1)
                  + " = '"
                  + item
                  + "'");
    query.exec();

    if (query.first()) {
        ui->lnEditRecurringPayment->setText(query.value(2).value<QString>());
    }
    else {
        incomesExpensesModel->setData(incomesExpensesModel->index(ui->cmbRecurringIncomesexpences->currentIndex() - 2, 2), item);
        incomesExpensesModel->submitAll();

        onGuiUpdate();
    }
}

void IncomesExpenses::onAddIncomesexpencesChanged(QString payment) {
    if (ui->cmbAddIncomesexpences->currentText() == "Выберете вариант"
            || ui->cmbAddIncomesexpences->currentText() == "")
    {
        ui->lnEditAddEdit->clear();
        return;
    }

    QSqlQuery query = incomesExpensesModel->query();
    query.prepare("SELECT * FROM "
                  + incomesExpensesModel->tableName()
                  + " WHERE "
                  + incomesExpensesModel->tableName().remove(incomesExpensesModel->tableName().size() - 1, 1)
                  + " = '"
                  + ui->cmbAddIncomesexpences->currentText()
                  + "'");
    query.exec();

    if (query.first()) {
        incomesExpensesModel->setData(incomesExpensesModel->index(ui->cmbAddIncomesexpences->currentIndex() - 2, 1), payment);
        incomesExpensesModel->submitAll();
    } else {
        int newRowIndex = incomesExpensesModel->rowCount();
        incomesExpensesModel->insertRow(newRowIndex);
        incomesExpensesModel->setData(incomesExpensesModel->index(newRowIndex, 0), ui->cmbAddIncomesexpences->currentText());
        incomesExpensesModel->setData(incomesExpensesModel->index(newRowIndex, 1), payment); // value
        incomesExpensesModel->setData(incomesExpensesModel->index(newRowIndex, 2), 0); // recurring
        incomesExpensesModel->setData(incomesExpensesModel->index(newRowIndex, 3), "1970-01-01");
        incomesExpensesModel->submitAll();

        onGuiUpdate();
    }
}

void IncomesExpenses::onRecurringChanged(QString payment) {
    if (ui->cmbRecurringIncomesexpences->currentText() == "Выберете вариант"
            || ui->cmbRecurringIncomesexpences->currentText() == "")
    {
        ui->lnEditRecurringPayment->clear();
        return;
    }

    QSqlQuery query = incomesExpensesModel->query();
    query.prepare("SELECT * FROM "
                  + incomesExpensesModel->tableName()
                  + " WHERE "
                  + incomesExpensesModel->tableName().remove(incomesExpensesModel->tableName().size() - 1, 1)
                  + " = '"
                  + ui->cmbAddIncomesexpences->currentText()
                  + "'");
    query.exec();

    query.first();
    incomesExpensesModel->setData(incomesExpensesModel->index(ui->cmbRecurringIncomesexpences->currentIndex() - 2, 2), payment);
    incomesExpensesModel->submitAll();
}

void IncomesExpenses::onItemRemove() {
    incomesExpensesModel->removeRow(ui->cmbAddIncomesexpences->currentIndex() - 2);
    incomesExpensesModel->submitAll();
    onGuiUpdate();
}

IncomesExpenses::~IncomesExpenses()
{
    delete ui;
}
