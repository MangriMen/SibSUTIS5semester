#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "goals.h"
#include "editfunds.h"
#include "incomesexpenses.h"
#include "accountcreation.h"
#include <QDebug>
#include <QDialog>
#include <QSqlDataBase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QMap>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(QString("Домашняя бухгалтерия"));

    QSqlDatabase usersDatabase = QSqlDatabase::addDatabase("QSQLITE", QLatin1String("users"));
    usersDatabase.setDatabaseName("./usersDatabase.db");
    usersDatabase.open();

    QSqlQuery usersQuery(usersDatabase);
    usersQuery.exec("CREATE TABLE Пользователи('Имя' TEXT, 'Последний' INT);");

    modelUsers = new QSqlTableModel(this, usersDatabase);
    modelUsers->setTable("Пользователи");
    modelUsers->select();

    QSqlQuery query = modelUsers->query();
    query.exec();
    if (query.first())
    {
        while (query.next())
        {
            if (query.value(1).value<int>() == true)
            {
                currentUserName = query.value(0).value<QString>().replace(" ", "");
            }
        }
    }
    else
    {
        accountCreation *newAcc = new accountCreation();
        if (newAcc->exec() == QDialog::Accepted)
        {
            modelUsers->insertRow(0);
            modelUsers->setData(modelUsers->index(0, 0), newAcc->getName());
            modelUsers->setData(modelUsers->index(0, 1), true);
            modelUsers->submitAll();
            currentUserName = newAcc->getName();
        }
        else
        {
            this->close();
            QTimer* tmr = new QTimer(this);
            tmr->setInterval(0);
            connect(tmr, &QTimer::timeout, [this](){
                this->close();
            });
            tmr->start();
        }
    }
    query.clear();

    currentUserName = latinize(currentUserName);

    QSqlDatabase accountingDatabase = QSqlDatabase::addDatabase("QSQLITE", QLatin1String("accounting"));
    accountingDatabase.setDatabaseName("./accounting" + currentUserName + ".db");
    accountingDatabase.open();

    QSqlQuery accountingQuery(accountingDatabase);
    accountingQuery.exec("CREATE TABLE Средства('Сумма в копилке' INT, 'Сумма в кошельке' INT, 'Автоматический перевод' INT, 'Дата последнего перевода' DATE);");
    accountingQuery.exec("CREATE TABLE Доходы('Доход' TEXT, 'Сумма' INT, 'Повторяющийся платёж' INT, 'Дата последнего платежа' DATE);");
    accountingQuery.exec("CREATE TABLE Расходы('Расход' TEXT, 'Сумма' INT, 'Повторяющийся платёж' INT, 'Дата последнего платежа' DATE);");
    accountingQuery.exec("CREATE TABLE Цели('Цель' TEXT, 'Стоимость' INT, 'Внесённая сумма' INT, 'Текущая' INT, 'Отменена' INT, 'Изображение' TEXT);");

    modelFunds = new QSqlTableModel(this, accountingDatabase);
    modelFunds->setTable("Средства");
    modelFunds->select();

    modelGoals = new QSqlTableModel(this, accountingDatabase);
    modelGoals->setTable("Цели");
    modelGoals->select();

    connect(ui->widFunds, &WidgetButton::clicked, this, &MainWindow::openFundsDialog);
    connect(ui->widGoals, &WidgetButton::clicked, this, &MainWindow::openGoalsDialog);
    connect(ui->grBoxIncomes, &WidgetButton::clicked, this, &MainWindow::openIncomesDialog);
    connect(ui->grBoxExpenses, &WidgetButton::clicked, this, &MainWindow::openExpencesDialog);
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

void MainWindow::onGuiUpdate()
{
    modelFunds->select();
    modelGoals->select();
    ui->listWidIncomes->clear();
    ui->listWidExpenses->clear();

    QSqlQuery query = modelFunds->query();
    query.exec();

    while (query.next())
    {
        int bank = query.value(0).value<int>();
        ui->lblBankBalance->setText(QString::number(bank));

        QString incomes = query.value(1).value<QString>();
        ui->listWidIncomes->addItems(incomes.split(';'));

        QString expenses = query.value(2).value<QString>();
        ui->listWidExpenses->addItems(expenses.split(';'));
    }
}

void MainWindow::onGoalBalanceModified()
{
    qDebug() << "goal balance modded";
}

void MainWindow::onAddToBankAccepted()
{
    qDebug() << "Add To Bank";
}

void MainWindow::onWithdrawFromBankAccepted()
{
    qDebug() << "Withdraw From Bank";
}

void MainWindow::onRecurringPaymentAccepted()
{
    qDebug() << "Recurring Payment Accepted";
}

void MainWindow::openGoalsDialog()
{
    Goals *goalsDialog = new Goals(this);

    connect(goalsDialog, &Goals::GoalBalanceModified, this, &MainWindow::onGoalBalanceModified);
    connect(goalsDialog, &Goals::finished, [=](int result)
            { goalsDialog->deleteLater(); });

    goalsDialog->open();
}

void MainWindow::openFundsDialog()
{
    EditFunds *fundsDialog = new EditFunds(this);

    connect(fundsDialog, &EditFunds::AddToBankAccepted, this, &MainWindow::onAddToBankAccepted);
    connect(fundsDialog, &EditFunds::WithdrawFromBankAccepted, this, &MainWindow::onWithdrawFromBankAccepted);
    connect(fundsDialog, &EditFunds::RecurringPaymentAccepted, this, &MainWindow::onRecurringPaymentAccepted);
    connect(fundsDialog, &EditFunds::finished, [=](int result)
            { fundsDialog->deleteLater(); });

    fundsDialog->open();
}

void MainWindow::openIncomesDialog()
{
    IncomesExpenses *incomesDialog = new IncomesExpenses(this);

    connect(incomesDialog, &IncomesExpenses::finished, [=](int result)
            { incomesDialog->deleteLater(); });

    incomesDialog->open();
}

void MainWindow::openExpencesDialog()
{
    IncomesExpenses *expencesDialog = new IncomesExpenses(this);

    connect(expencesDialog, &IncomesExpenses::finished, [=](int result)
            { expencesDialog->deleteLater(); });

    expencesDialog->open();
}

MainWindow::~MainWindow()
{
    delete ui;
}
