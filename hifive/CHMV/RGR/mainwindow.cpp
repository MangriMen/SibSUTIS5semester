#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "goals.h"
#include "editfunds.h"
#include "incomesexpenses.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->widFunds, &WidgetButton::clicked, this, &MainWindow::openFundsDialog);
    connect(ui->widGoals, &WidgetButton::clicked, this, &MainWindow::openGoalsDialog);
    connect(ui->grBoxIncomes, &WidgetButton::clicked, this, &MainWindow::openIncomesDialog);
    connect(ui->grBoxExpenses, &WidgetButton::clicked, this, &MainWindow::openExpencesDialog);
}

void MainWindow::onGoalBalanceModified() {
    qDebug() << "goal balance modded";
}

void MainWindow::onAddToBankAccepted() {
    qDebug() << "Add To Bank";
};

void MainWindow::onWithdrawFromBankAccepted() {
    qDebug() << "Withdraw From Bank";
};

void MainWindow::onRecurringPaymentAccepted() {
    qDebug() << "Recurring Payment Accepted";
};

void MainWindow::openGoalsDialog() {
    Goals *goalsDialog = new Goals(this);

    connect(goalsDialog, &Goals::GoalBalanceModified, this, &MainWindow::onGoalBalanceModified);
    connect(goalsDialog, &Goals::finished, [=](int result){
        goalsDialog->deleteLater();
    });

    goalsDialog->open();
}

void MainWindow::openFundsDialog() {
    EditFunds *fundsDialog = new EditFunds(this);

    connect(fundsDialog, &EditFunds::finished, [=](int result){
        fundsDialog->deleteLater();
    });

    fundsDialog->open();
}

void MainWindow::openIncomesDialog() {
    IncomesExpenses *incomesDialog = new IncomesExpenses(this);

    connect(incomesDialog, &IncomesExpenses::finished, [=](int result){
        incomesDialog->deleteLater();
    });

    incomesDialog->open();
}

void MainWindow::openExpencesDialog() {
    IncomesExpenses *expencesDialog = new IncomesExpenses(this);

    connect(expencesDialog, &IncomesExpenses::finished, [=](int result){
        expencesDialog->deleteLater();
    });

    expencesDialog->open();
}

MainWindow::~MainWindow()
{
    delete ui;
}
