#include "goals.h"
#include "ui_goals.h"
#include "labelbutton.h"
#include <QSqlQuery>
#include <QFileDialog>

Goals::Goals(QSqlTableModel *modelGoals, QSqlTableModel *modelFunds, QWidget *parent) :
    QDialog(parent),
    goalsModel(modelGoals),
    fundsModel(modelFunds),
    ui(new Ui::Goals)
{
    ui->setupUi(this);

    this->setWindowFlags(this->windowFlags().setFlag(Qt::WindowContextHelpButtonHint, false));

    ui->lnEditGoalPrice->setValidator(new QIntValidator(0, 9999999, this));
    ui->lnEditTransfer->setValidator(new QIntValidator(0, 9999999, this));
    ui->lnEditWithdraw->setValidator(new QIntValidator(0, 9999999, this));

    onGuiUpdate();

    connect(ui->cmbAddGoal, SIGNAL(currentIndexChanged(QString)), this, SLOT(onAddGoalIndexChanged(QString)));
    connect(ui->lnEditGoalPrice, &ELineEdit::textEdited, this, &Goals::onGoalPriceChanged);
    connect(ui->btnDeleteGoal, &QPushButton::clicked, this, &Goals::onItemRemove);

    connect(ui->lblAddEditImage, SIGNAL(clicked()), this, SLOT(onGoalImageChanged()));
}

Goals::~Goals()
{
    delete ui;
}

void Goals::onGuiUpdate() {
    goalsModel->select();
    QSqlQuery query = goalsModel->query();
    query.exec();

    QString cmbAddGoalSelected = ui->cmbAddGoal->currentText();

    ui->cmbAddGoal->clear();
    ui->cmbAddGoal->addItem("Выберете вариант");
    ui->cmbAddGoal->insertSeparator(1);

    bool atLeastOneGoalChoosed = false;
    int childrenCount = 0;
    while (query.next())
    {
        QString item = query.value(0).value<QString>();
        ui->cmbAddGoal->addItem(item);

        if (query.value(3).toBool()) {
            atLeastOneGoalChoosed = true;
            if (query.value(4).toBool()) {
                QFont font = QFont(ui->lblCurrentGoalNameText->font());
                font.setStrikeOut(true);
                ui->lblCurrentGoalNameText->setFont(font);
            } else {
                QFont font = QFont(ui->lblCurrentGoalNameText->font());
                font.setStrikeOut(false);
                ui->lblCurrentGoalNameText->setFont(font);
            }
            ui->lblCurrentGoalNameText->setText(query.value(0).toString());
            ui->lblCurrentGoalPrice->setText(query.value(1).toString() + "р");
            ui->lblCurrentGoalMoneySpent->setText(query.value(2).toString() + "р");
            if (!query.value(5).toString().isEmpty()) {
                ui->lblCurrentGoalImage->setPixmap(QPixmap(query.value(5).toString()));
            }
            else {
                ui->lblCurrentGoalImage->setPixmap(QPixmap(":/images/image_black_24dp.svg"));
            }
        }
        childrenCount++;
    }

    if(!atLeastOneGoalChoosed) {
        ui->lblCurrentGoalNameText->setText("Текущая цель не выбрана");
        ui->lblCurrentGoalPrice->setText("0р");
        ui->lblCurrentGoalMoneySpent->setText("0р");
        ui->lblCurrentGoalImage->setPixmap(QPixmap(":/images/image_black_24dp.svg"));
    }

    fundsModel->select();
    QSqlQuery fundsQuery = fundsModel->query();
    fundsQuery.exec();

    if (fundsQuery.first()) {
        ui->lblBankBalance->setText(fundsQuery.value(0).value<QString>());
    }

    ui->cmbAddGoal->insertSeparator(childrenCount + 2);
    ui->cmbAddGoal->addItem("Добавить");

    if (!cmbAddGoalSelected.isEmpty()) {
        ui->cmbAddGoal->setCurrentText(cmbAddGoalSelected);
    }

    ui->cmbAddGoal->currentTextChanged(ui->cmbAddGoal->currentText());
}

void Goals::onAddGoalIndexChanged(QString item) {
    if (item == "Выберете вариант" || item == "") {
        ui->cmbAddGoal->setEditable(false);
        ui->lnEditGoalPrice->clear();
        ui->lblAddEditImage->setPixmap(QPixmap(":/images/image_black_24dp.svg"));
        return;
    }
    ui->cmbAddGoal->setEditable(true);
    ui->cmbAddGoal->lineEdit()->setFont(ui->cmbAddGoal->font());

    if (item == "Добавить") {
        ui->cmbAddGoal->lineEdit()->clear();
        ui->lnEditGoalPrice->clear();
        ui->lblAddEditImage->setPixmap(QPixmap(":/images/image_black_24dp.svg"));
        return;
    }

    QSqlQuery query = goalsModel->query();
    query.prepare("SELECT * FROM "
                  + goalsModel->tableName()
                  + " WHERE "
                  + "Цель"
                  + " = '"
                  + item
                  + "'");
    query.exec();

    if (query.first()) {
        ui->lnEditGoalPrice->setText(query.value(1).value<QString>());
        if (!query.value(5).toString().isEmpty()) {
            ui->lblAddEditImage->setPixmap(QPixmap(query.value(5).toString()).scaled(100, 100));
        }
        else {
            ui->lblAddEditImage->setPixmap(QPixmap(":/images/image_black_24dp.svg"));
        }
    } else {
        int newRowIndex = goalsModel->rowCount();
        goalsModel->insertRow(newRowIndex);
        goalsModel->setData(goalsModel->index(newRowIndex, 0), item);
        goalsModel->setData(goalsModel->index(newRowIndex, 1), 0);
        goalsModel->setData(goalsModel->index(newRowIndex, 2), 0);
        goalsModel->setData(goalsModel->index(newRowIndex, 3), 0);
        goalsModel->setData(goalsModel->index(newRowIndex, 4), 0);
        goalsModel->setData(goalsModel->index(newRowIndex, 5), "");
        goalsModel->submitAll();

        onGuiUpdate();
    }
}

void Goals::onGoalPriceChanged(QString item) {
    if (ui->cmbAddGoal->currentText() == "Выберете вариант" || ui->cmbAddGoal->currentText() == "") {
        ui->lnEditGoalPrice->clear();
        return;
    }

    goalsModel->select();
    goalsModel->setData(goalsModel->index(ui->cmbAddGoal->currentIndex() - 2, 1), item);
    goalsModel->submitAll();

    onGuiUpdate();
}

void Goals::onGoalImageChanged() {
    QString filename = QFileDialog::getOpenFileName(this, "Загрузка картинки", "");

    goalsModel->select();
    goalsModel->setData(goalsModel->index(ui->cmbAddGoal->currentIndex() - 2, 5), filename);
    goalsModel->submitAll();

    onGuiUpdate();
}

void Goals::onItemRemove() {
    goalsModel->removeRow(ui->cmbAddGoal->currentIndex() - 2);
    goalsModel->submitAll();
    onGuiUpdate();
}

void Goals::on_btnTransferAccept_clicked()
{
    QModelIndexList Items = goalsModel->match(
                goalsModel->index(0, 0),
                Qt::DisplayRole,
                ui->lblCurrentGoalNameText->text());
    GoalBalanceModified(ui->lnEditTransfer->text().toInt(), Items.first().row());
    onGuiUpdate();
}

void Goals::on_btnWithdrawAccept_clicked()
{
    QModelIndexList Items = goalsModel->match(
                goalsModel->index(0, 0),
                Qt::DisplayRole,
                ui->lblCurrentGoalNameText->text());
    GoalBalanceModified(-ui->lnEditWithdraw->text().toInt(), Items.first().row());
    onGuiUpdate();
}


void Goals::on_btnMakeCurrent_clicked()
{
    goalsModel->select();

    for (int i = 0; i < goalsModel->rowCount(); i++) {
        if (goalsModel->index(i, 0).data().toString() != ui->cmbAddGoal->currentText()) {
            goalsModel->setData(goalsModel->index(i, 3), false);
        }
        else {
            goalsModel->setData(goalsModel->index(i, 3), true);
        }
        goalsModel->submitAll();
    }

    onGuiUpdate();
}

void Goals::on_btnDiscardGoal_clicked()
{
    goalsModel->select();

    goalsModel->setData(goalsModel->index(ui->cmbAddGoal->currentIndex() - 2, 4), true);

    goalsModel->submitAll();

    onGuiUpdate();
}
