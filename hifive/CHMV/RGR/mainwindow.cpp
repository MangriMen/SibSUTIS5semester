#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "goals.h"
#include "editfunds.h"
#include "incomesexpenses.h"
#include "accountcreation.h"
#include <cstdio>
#include <QDebug>
#include <QDialog>
#include <QSqlDataBase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QMap>
#include <QVariant>
#include <QTimer>
#include <QSettings>
#include <fstream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(QString("Домашняя бухгалтерия"));

    QCoreApplication::setOrganizationName("HI5.INC");
    QCoreApplication::setApplicationName("RGR");

    QSqlDatabase usersDatabase = QSqlDatabase::addDatabase("QSQLITE", QLatin1String("users"));
    usersDatabase.setDatabaseName("./usersDatabase.db");
    usersDatabase.open();

    QSqlQuery usersQuery(usersDatabase);
    usersQuery.exec("CREATE TABLE Пользователи('Имя' TEXT UNIQUE);");
    usersQuery.clear();

    modelUsers = new QSqlTableModel(this, usersDatabase);
    modelUsers->setTable("Пользователи");
    modelUsers->select();

    if (!loadUsers() && !onNewUserRequested())
    {
        QTimer* tmr = new QTimer(this);
        tmr->setInterval(0);
        connect(tmr, &QTimer::timeout, [this](){
            this->close();
        });
        tmr->start();
    }

    onGuiUpdate();

    connect(ui->widFunds, &WidgetButton::clicked, this, &MainWindow::openFundsDialog);
    connect(ui->widGoals, &WidgetButton::clicked, this, &MainWindow::openGoalsDialog);
    connect(ui->grBoxIncomes, &WidgetButton::clicked, this, &MainWindow::openIncomesDialog);
    connect(ui->grBoxExpenses, &WidgetButton::clicked, this, &MainWindow::openExpencesDialog);
    connect(ui->btnAccountDelete, &QPushButton::clicked, this, &MainWindow::onUserDeleteRequested);
}

bool MainWindow::loadUsers() {
    ui->menuBtnUser->clear();

    modelUsers->select();
    QSqlQuery query = modelUsers->query();
    query.exec();

    QActionGroup* usersMenu = new QActionGroup(this);
    connect(usersMenu, &QActionGroup::triggered, this, &MainWindow::onUserChanged);

    const bool isUsersTableEmpty = modelUsers->rowCount() == 0;
    if (!isUsersTableEmpty)
    {
        while (query.next())
        {
            QAction* addedUser = usersMenu->addAction(query.value(0).value<QString>());
            addedUser->setCheckable(true);
        }

        QAction* selectedUser = nullptr;
        if (currentUserName() == "") {
            selectedUser = usersMenu->actions().first();
        } else {
            foreach (QAction* action, usersMenu->actions()) {
                if (action->text() == currentUserName()) {
                    selectedUser = action;
                    break;
                }
            }
        }
        ui->menuBtnUser->addActions(usersMenu->actions());
        ui->menuBtnUser->addSeparator();
        QAction* addUserButton = ui->menuBtnUser->addAction("Новый пользователь");
        connect(addUserButton, &QAction::triggered, this, &MainWindow::onNewUserRequested);

        selectedUser->setChecked(true);
        selectedUser->trigger();

        onGuiUpdate();
    }

    return !isUsersTableEmpty;
}

const QString MainWindow::currentUserName() {
    return QSettings(this).value("lastUser", "").toString();
}

void MainWindow::setCurrentUserName(QString userName) {
    QSettings(this).setValue("lastUser", userName);
}

QString MainWindow::latinize(QString str)
{
    QMap<QChar, QString> t;

    t[0x430] = "a";
    t[0x431] = "b";
    t[0x432] = "v";
    t[0x433] = "g";
    t[0x434] = "d";
    t[0x435] = "e";
    t[0x451] = "yo";
    t[0x436] = "j";
    t[0x437] = "z";
    t[0x438] = "i";
    t[0x439] = "iy";
    t[0x43A] = "k";
    t[0x43B] = "l";
    t[0x43C] = "m";
    t[0x43D] = "n";
    t[0x43E] = "o";
    t[0x43F] = "p";
    t[0x440] = "r";
    t[0x441] = "s";
    t[0x442] = "t";
    t[0x443] = "y";
    t[0x444] = "f";
    t[0x445] = "h";
    t[0x446] = "c";
    t[0x447] = "ch";
    t[0x448] = "sh";
    t[0x449] = "she";
    t[0x44A] = "";
    t[0x44B] = "i";
    t[0x44C] = "";
    t[0x44D] = "ye";
    t[0x44E] = "u";
    t[0x44F] = "ya";

    t[0x410] = "A";
    t[0x411] = "B";
    t[0x412] = "V";
    t[0x413] = "G";
    t[0x414] = "D";
    t[0x415] = "E";
    t[0x401] = "Yo";
    t[0x416] = "J";
    t[0x417] = "Z";
    t[0x418] = "I";
    t[0x419] = "Iy";
    t[0x41A] = "K";
    t[0x41B] = "L";
    t[0x41C] = "M";
    t[0x41D] = "N";
    t[0x41E] = "O";
    t[0x41F] = "P";
    t[0x420] = "R";
    t[0x421] = "S";
    t[0x422] = "T";
    t[0x423] = "Y";
    t[0x424] = "F";
    t[0x425] = "H";
    t[0x426] = "C";
    t[0x427] = "Ch";
    t[0x428] = "Sh";
    t[0x429] = "She";
    t[0x42A] = "";
    t[0x42B] = "I";
    t[0x42C] = "";
    t[0x42D] = "Ye";
    t[0x42E] = "U";
    t[0x42F] = "Ya";

    QString result;

    foreach (QChar ch, str)
    {
        result += (t.contains(ch)) ? t[ch] : ch;
    }

    return result;
}

void MainWindow::closeDatabase() {
    QSqlDatabase accountingDatabase = QSqlDatabase::database("accounting", false);
    accountingDatabase.close();
}

bool MainWindow::onNewUserRequested() {
    accountCreation *newAcc = new accountCreation();

    const bool isUserCreated = newAcc->exec() == QDialog::Accepted;

    if (isUserCreated)
    {
        modelUsers->insertRow(0);
        modelUsers->setData(modelUsers->index(0, 0), newAcc->getName());
        modelUsers->submitAll();
        setCurrentUserName(newAcc->getName());

        loadUsers();
    }

    newAcc->deleteLater();
    return isUserCreated;
}

bool MainWindow::onUserDeleteRequested() {
    const bool result = modelUsers->removeRow(
                    modelUsers->match(modelUsers->index(0,0), Qt::DisplayRole, QVariant::fromValue(currentUserName())).first().row()
                );

    closeDatabase();
    QFile::remove("./accounting" +  latinize(currentUserName()).replace(" ","") + ".db");
    setCurrentUserName("");

    if (!loadUsers()) {
        if (!onNewUserRequested()) {
            close();
        }
    }

    return result;
}

void MainWindow::onUserChanged(QAction* selectedUser) {
    setCurrentUserName(selectedUser->text());

    closeDatabase();
    QSqlDatabase accountingDatabase = QSqlDatabase::database("accounting", false);
    if (!accountingDatabase.isValid()) {
        accountingDatabase = QSqlDatabase::addDatabase("QSQLITE", QLatin1String("accounting"));
    }
    accountingDatabase.setDatabaseName("./accounting" +  latinize(currentUserName()).replace(" ","") + ".db");
    accountingDatabase.open();

    QSqlQuery accountingQuery(accountingDatabase);
    accountingQuery.exec("CREATE TABLE Средства('Сумма в копилке' INT, 'Сумма в кошельке' INT, 'Автоматический перевод' INT, 'Дата последнего перевода' DATE);");
    accountingQuery.exec("CREATE TABLE Доходы('Доход' TEXT, 'Сумма' INT, 'Повторяющийся платёж' INT, 'Дата последнего платежа' DATE);");
    accountingQuery.exec("CREATE TABLE Расходы('Расход' TEXT, 'Сумма' INT, 'Повторяющийся платёж' INT, 'Дата последнего платежа' DATE);");
    accountingQuery.exec("CREATE TABLE Цели('Цель' TEXT, 'Стоимость' INT, 'Внесённая сумма' INT, 'Текущая' INT, 'Отменена' INT, 'Изображение' TEXT);");

    modelFunds = new QSqlTableModel(this, accountingDatabase);
    modelFunds->setTable("Средства");
    modelFunds->select();
    if (modelFunds->rowCount() == 0) {
        modelFunds->insertRow(0);
        modelFunds->setData(modelFunds->index(0, 0), 0);
        modelFunds->setData(modelFunds->index(0, 1), 0);
        modelFunds->setData(modelFunds->index(0, 2), 0);
        modelFunds->setData(modelFunds->index(0, 3), "01.01.1970");
        modelFunds->submitAll();
    }

    modelGoals = new QSqlTableModel(this, accountingDatabase);
    modelGoals->setTable("Цели");
    modelGoals->select();

    modelIncomes = new QSqlTableModel(this, accountingDatabase);
    modelIncomes->setTable("Доходы");
    modelIncomes->select();

    modelExpenses = new QSqlTableModel(this, accountingDatabase);
    modelExpenses->setTable("Расходы");
    modelExpenses->select();

    ui->listWidIncomes->setModel(modelIncomes);
    ui->listWidIncomes->setColumnHidden(2, true);
    ui->listWidIncomes->setColumnHidden(3, true);
    ui->listWidIncomes->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->listWidIncomes->setCursor(Qt::ArrowCursor);

    ui->listWidExpenses->setModel(modelExpenses);
    ui->listWidExpenses->setColumnHidden(2, true);
    ui->listWidExpenses->setColumnHidden(3, true);
    ui->listWidExpenses->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->listWidExpenses->setCursor(Qt::ArrowCursor);

    ui->lblAccountName->setText(currentUserName());

    onGuiUpdate();
}

void MainWindow::onGuiUpdate()
{
    modelFunds->select();
    modelExpenses->select();
    modelIncomes->select();
    modelGoals->select();

    QSqlQuery fundsQuery = modelFunds->query();
    fundsQuery.exec();
    QSqlQuery incomesQuery = modelIncomes->query();
    incomesQuery.exec();
    QSqlQuery expensesQuery = modelExpenses->query();
    expensesQuery.exec();

    while (fundsQuery.next())
    {
        int wallet = fundsQuery.value(1).value<int>();
        ui->lblWalletBalance->setText(QString::number(wallet));

        int bank = fundsQuery.value(0).value<int>();
        ui->lblBankBalance->setText(QString::number(bank));
    }

    ui->lblIncomesTotal->setText(QString::number(0));
    int incomesTotal = 0;
    while (incomesQuery.next())
    {
        incomesTotal += incomesQuery.value(1).toInt();
    }
    ui->lblIncomesTotal->setText("+" + QString::number(incomesTotal) + "р");

    ui->lblExpensesTotal->setText(QString::number(0));
    int expensesTotal = 0;
    while (expensesQuery.next())
    {
        expensesTotal += expensesQuery.value(1).toInt();
    }
    ui->lblExpensesTotal->setText("-" + QString::number(expensesTotal) + "р");

    QSqlQuery goalsQuery = modelGoals->query();
    goalsQuery.exec();

    bool atLeastOneGoalChoosed = false;
    while (goalsQuery.next()) {
        if (goalsQuery.value(3).toBool()) {
            ui->lblCurrentGoalText->setText(goalsQuery.value(0).toString());
            if (goalsQuery.value(4).toBool()) {
                QFont font = QFont(ui->lblCurrentGoalText->font());
                font.setStrikeOut(true);
                ui->lblCurrentGoalText->setFont(font);
            } else {
                QFont font = QFont(ui->lblCurrentGoalText->font());
                font.setStrikeOut(false);
                ui->lblCurrentGoalText->setFont(font);
            }
            if (!goalsQuery.value(5).toString().isEmpty()) {
                ui->lblCurrentGoalImg->setPixmap(QPixmap(goalsQuery.value(5).toString()).scaled(100, 100));
            }
            else {
                ui->lblCurrentGoalImg->setPixmap(QPixmap(":/images/image_black_24dp.svg"));
            }
            ui->lblCurrentGoalMoneySpent->setText(goalsQuery.value(2).toString() + "р");
            ui->lblCurrentGoalPrice->setText(goalsQuery.value(1).toString() + "р");
            atLeastOneGoalChoosed = true;
            break;
        }
    }
    if (!atLeastOneGoalChoosed) {
        ui->lblCurrentGoalText->setText("Нет цели");
        ui->lblCurrentGoalMoneySpent->setText("0р");
        ui->lblCurrentGoalPrice->setText("0р");
        ui->lblCurrentGoalImg->setPixmap(QPixmap(":/images/image_black_24dp.svg"));
    }
}

void MainWindow::onGoalBalanceModified(int diff, int index)
{
    modelFunds->select();
    modelGoals->select();
    int newPrice = modelGoals->index(index, 2).data().toInt() + diff;
    int newBank = modelFunds->index(0, 0).data().toInt() - diff;
    if (newPrice >= 0 && newBank >= 0) {
        modelGoals->setData(modelGoals->index(index, 2), newPrice);
        modelFunds->setData(modelFunds->index(0, 0), newBank);
    }
    modelGoals->submitAll();
    modelFunds->submitAll();
    onGuiUpdate();
}

void MainWindow::onAddToWalletAccepted(int number)
{
    modelFunds->select();
    modelFunds->setData(modelFunds->index(0, 1), modelFunds->data(modelFunds->index(0, 1)).toInt() + number);
    modelFunds->submitAll();

    onGuiUpdate();
}

void MainWindow::onAddToBankAccepted(int number)
{
    modelFunds->select();
    modelFunds->setData(modelFunds->index(0, 0), modelFunds->data(modelFunds->index(0, 0)).toInt() + number);
    modelFunds->setData(modelFunds->index(0, 1), modelFunds->data(modelFunds->index(0, 1)).toInt() - number);
    modelFunds->submitAll();

    onGuiUpdate();
}

void MainWindow::onWithdrawFromBankAccepted(int number)
{
    modelFunds->select();
    modelFunds->setData(modelFunds->index(0, 0), modelFunds->data(modelFunds->index(0, 0)).toInt() - number);
    modelFunds->submitAll();

    onGuiUpdate();
}

void MainWindow::onRecurringPaymentAccepted()
{
//    modelFunds->setData(modelFunds->index(0, 2), ln.text().toInt());
    onGuiUpdate();
}

void MainWindow::openGoalsDialog()
{
    Goals *goalsDialog = new Goals(modelGoals, modelFunds, this);

    connect(goalsDialog, &Goals::GoalBalanceModified, this, &MainWindow::onGoalBalanceModified);
    connect(goalsDialog, &Goals::finished, [=]() {
        onGuiUpdate();
        goalsDialog->deleteLater();
    });

    goalsDialog->open();
}

void MainWindow::openFundsDialog()
{
    EditFunds *fundsDialog = new EditFunds(modelFunds, this);

    connect(fundsDialog, &EditFunds::AddToWalletAccepted, this, &MainWindow::onAddToWalletAccepted);
    connect(fundsDialog, &EditFunds::AddToBankAccepted, this, &MainWindow::onAddToBankAccepted);
    connect(fundsDialog, &EditFunds::WithdrawFromBankAccepted, this, &MainWindow::onWithdrawFromBankAccepted);
    connect(fundsDialog, &EditFunds::RecurringPaymentAccepted, this, &MainWindow::onRecurringPaymentAccepted);
    connect(fundsDialog, &EditFunds::finished, [=](int result)
            { fundsDialog->deleteLater(); });

    fundsDialog->open();
}

void MainWindow::openIncomesDialog()
{
    IncomesExpenses *incomesDialog = new IncomesExpenses(modelIncomes, "Доходы", this);

    connect(this, &MainWindow::incomesExpensesGuiUpdate, incomesDialog, &IncomesExpenses::onGuiUpdate);
    connect(incomesDialog, &IncomesExpenses::finished, [=](int result) {
        onGuiUpdate();
        incomesDialog->deleteLater();
    });

    incomesDialog->open();
}

void MainWindow::openExpencesDialog()
{
    IncomesExpenses *expencesDialog = new IncomesExpenses(modelExpenses, "Расходы", this);

    connect(expencesDialog, &IncomesExpenses::finished, [=](int result) {
        onGuiUpdate();
        expencesDialog->deleteLater();
    });

    expencesDialog->open();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionInfo_triggered()
{
    QProcess *process = new QProcess;
    QStringList args;
    args << QLatin1String("-collectionFile")
        << QLatin1String("collection.qhc")
        << QLatin1String("-enableRemoteControl");
    process->start(QLatin1String("assistant"), args);

    if (!process->waitForStarted()) { return;}
}
