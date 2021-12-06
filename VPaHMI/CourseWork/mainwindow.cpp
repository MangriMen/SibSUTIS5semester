#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    affairsBase = QSqlDatabase::addDatabase("QSQLITE");
    affairsBase.setDatabaseName("./affairsBase.db");
    affairsBase.open();

    QSqlQuery query(affairsBase);
    query.exec("CREATE TABLE Учебные(Предмет TEXT, Задание TEXT, 'Срок сдачи' DATE);");
    query.exec("CREATE TABLE Рабочие(Задание TEXT, 'Срок сдачи' DATE);");
    query.exec("CREATE TABLE Личные(Задание TEXT);");
    query.exec("CREATE TABLE Места(Задание TEXT);");
    query.exec("CREATE TABLE Понедельник(Время DATE, Задание TEXT, Описание TEXT, Год INT, Неделя INT);");
    query.exec("CREATE TABLE Вторник(Время DATE, Задание TEXT, Описание TEXT, Год INT, Неделя INT);");
    query.exec("CREATE TABLE Среда(Время DATE, Задание TEXT, Описание TEXT, Год INT, Неделя INT);");
    query.exec("CREATE TABLE Четверг(Время DATE, Задание TEXT, Описание TEXT, Год INT, Неделя INT);");
    query.exec("CREATE TABLE Пятница(Время DATE, Задание TEXT, Описание TEXT, Год INT, Неделя INT);");
    query.exec("CREATE TABLE Суббота(Время DATE, Задание TEXT, Описание TEXT, Год INT, Неделя INT);");
    query.exec("CREATE TABLE Воскресенье(Время DATE, Задание TEXT, Описание TEXT, Год INT, Неделя INT);");
    query.exec("CREATE TABLE Любой(Время DATE, Задание TEXT, Описание TEXT, Год INT, Неделя INT);");
    query.exec("CREATE TABLE ТипДня(Тип INT, День DATE UNIQUE);");

    educationModel = new QSqlTableModel(this, affairsBase);
    educationModel->setTable("Учебные");
    educationModel->select();

    workModel = new QSqlTableModel(this, affairsBase);
    workModel->setTable("Рабочие");
    workModel->select();

    personalModel = new QSqlTableModel(this, affairsBase);
    personalModel->setTable("Личные");
    personalModel->select();

    placesModel = new QSqlTableModel(this, affairsBase);
    placesModel->setTable("Места");
    placesModel->select();

    ui->dayMonday->setTitle(tr("Monday"));
    ui->dayTuesday->setTitle(tr("Tuesday"));
    ui->dayWednesday->setTitle(tr("Wednesday"));
    ui->dayThursday->setTitle(tr("Thursday"));
    ui->dayFriday->setTitle(tr("Friday"));
    ui->daySaturday->setTitle(tr("Saturday"));
    ui->daySunday->setTitle(tr("Sunday"));
    ui->dayAny->setTitle(tr("Week"));

    ui->dayMonday->setDayNum(HeaderTableItem::WeekDay::Monday);
    ui->dayTuesday->setDayNum(HeaderTableItem::WeekDay::Tuesday);
    ui->dayWednesday->setDayNum(HeaderTableItem::WeekDay::Wednesday);
    ui->dayThursday->setDayNum(HeaderTableItem::WeekDay::Thursday);
    ui->dayFriday->setDayNum(HeaderTableItem::WeekDay::Friday);
    ui->daySaturday->setDayNum(HeaderTableItem::WeekDay::Saturday);
    ui->daySunday->setDayNum(HeaderTableItem::WeekDay::Sunday);
    ui->dayAny->setDayNum(HeaderTableItem::WeekDay::Any);

    QList<HeaderTableItem*> days {
        ui->dayMonday,
        ui->dayTuesday,
        ui->dayWednesday,
        ui->dayThursday,
        ui->dayFriday,
        ui->daySaturday,
        ui->daySunday,
        ui->dayAny
    };

    foreach (HeaderTableItem* item, days) {
        item->setType(HeaderTableItem::Type::Day);
        connect(item, SIGNAL(btnCofifguredClicked(HeaderTableItem*)), this, SLOT(onConfigurePageRequested(HeaderTableItem*)));
        QSqlTableModel* tempModel = new QSqlTableModel(this, affairsBase);
        tempModel->setTable(item->getDayDBName());
        item->setTableModel(tempModel);
        item->updateModel();
        QDate date = QDate::currentDate();
        date.setDate(date.year(), date.month(), item->getDay().toInt());
        QSqlQuery* dayTypeQuery = new QSqlQuery();
        dayTypeQuery->prepare("SELECT Тип FROM ТипДня WHERE День = ?");
        dayTypeQuery->bindValue(0, date);
        dayTypeQuery->exec();
        if (dayTypeQuery->next()) {
            item->setDayType(static_cast<HeaderTableItem::DayType>(dayTypeQuery->value(0).value<int>()));
        }
        dayTypeQuery->clear();
        delete dayTypeQuery;
    }

    ui->tableEducationAffairs->setTitle(tr("Education affairs"));
    ui->tableWorkAffairs->setTitle(tr("Work affairs"));
    ui->tablePersonalAffairs->setTitle(tr("Personal affairs"));
    ui->tablePlaces->setTitle(tr("Places"));

    ui->tableEducationAffairs->setType(HeaderTableItem::Type::Education);
    ui->tableWorkAffairs->setType(HeaderTableItem::Type::Work);
    ui->tablePersonalAffairs->setType(HeaderTableItem::Type::Personal);
    ui->tablePlaces->setType(HeaderTableItem::Type::Places);

    ui->tableEducationAffairs->setTableModel(educationModel);
    ui->tableWorkAffairs->setTableModel(workModel);
    ui->tablePersonalAffairs->setTableModel(personalModel);
    ui->tablePlaces->setTableModel(placesModel);

    QList<HeaderTableItem*> tables {
        ui->tableEducationAffairs,
        ui->tableWorkAffairs,
        ui->tablePersonalAffairs,
        ui->tablePlaces,
    };
    foreach (HeaderTableItem* item, tables) {
        connect(item, SIGNAL(btnCofifguredClicked(HeaderTableItem*)), this, SLOT(onConfigurePageRequested(HeaderTableItem*)));
    }

    connect(ui->actionHelp, SIGNAL(triggered(bool)), this, SLOT(onHelpRequested()));
    connect(ui->btnSelectWeek, SIGNAL(clicked(bool)), this, SLOT(onWeekChangeRequested()));

    ui->layoutHolder->addWidget(ui->twNavigation);

    setCurrentWeek(QDate::currentDate());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCurrentWeek(QDate date) {
    QDate weekStart = date;
    if (weekStart.dayOfWeek() != 1) {
        weekStart = weekStart.addDays(-weekStart.dayOfWeek() + 1);
    }
    currentWeek = weekStart;
    ui->lblChoosedYear->setText(QString::number(currentWeek.year()));
    ui->lblChoosedWeek->setText(QString::number(currentWeek.weekNumber()) + " - " + QString::number(currentWeek.addDays(7).weekNumber()));
}

void MainWindow::onHelpRequested() {
    QMessageBox::information(this, "Help", "Help");
}

void MainWindow::onConfigurePageRequested(HeaderTableItem *item) {
    ui->twNavigation->setVisible(false);
    ui->btnSelectWeek->setEnabled(false);
    ui->btnWeekNext->setEnabled(false);
    ui->btnWeekPrevious->setEnabled(false);

    HeaderTableItemEditPage* editPage = new HeaderTableItemEditPage(this, item);
    connect(editPage, SIGNAL(btnBackClicked()), this, SLOT(onRestoreNavigationRequested()));
    savedTab = editPage;

    ui->layoutHolder->addWidget(editPage);
}

void MainWindow::onRestoreNavigationRequested() {
    ui->twNavigation->setVisible(true);
    ui->layoutHolder->removeWidget(savedTab);
    ui->btnSelectWeek->setEnabled(true);
    ui->btnWeekNext->setEnabled(true);
    ui->btnWeekPrevious->setEnabled(true);

    delete savedTab;
}

void MainWindow::onWeekChangeRequested() {
    DatePopup* calendar = new DatePopup(this);
    calendar->exec();
}
