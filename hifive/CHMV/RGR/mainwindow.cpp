#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->widFunds, &WidgetButton::clicked, [this](){ qDebug() << "funds"; });
    connect(ui->widGoals, &WidgetButton::clicked, [this](){ qDebug() << "goals"; });
    connect(ui->grBoxIncomes, &WidgetButton::clicked, [this](){ qDebug() << "incomes"; });
    connect(ui->grBoxExpenses, &WidgetButton::clicked, [this](){ qDebug() << "expences"; });
}

MainWindow::~MainWindow()
{
    delete ui;
}
