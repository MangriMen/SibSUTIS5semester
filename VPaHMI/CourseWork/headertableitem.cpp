#include "headertableitem.h"
#include "ui_headertableitem.h"
#include "headertableitemeditpage.h"

HeaderTableItem::HeaderTableItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HeaderTableItem)
{
    ui->setupUi(this);
    ui->tblData->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    setWeekNum(QDateTime::currentDateTime().date().weekNumber());
    setYearNum(QDateTime::currentDateTime().date().year());
    ui->frameHeader->setStyleSheet("QFrame {background-color: white;}");
}

HeaderTableItem::~HeaderTableItem()
{
    delete ui;
}

void HeaderTableItem::setTitle(QString title) {
    ui->lblHeader->setText(title);
}

QString HeaderTableItem::getTitle() {
    return ui->lblHeader->text();
}

void HeaderTableItem::setDay(QString day) {
    ui->lblDay->setText(day);
}

QString HeaderTableItem::getDay() {
    return ui->lblDay->text();
}

void HeaderTableItem::setDayType(HeaderTableItem::DayType type) {
    dayType_ = type;

    switch (dayType_) {
    case DayType::Work:
        ui->frameHeader->setStyleSheet("QFrame {background-color: #E57373;}");
        break;
    case DayType::Education:
        ui->frameHeader->setStyleSheet("QFrame {background-color: #64B5F6;}");
        break;
    case DayType::EducationAndWork:
        ui->frameHeader->setStyleSheet("QFrame {background-color: #9575CD;}");
        break;
    case DayType::DayOff:
        ui->frameHeader->setStyleSheet("QFrame {background-color: white;}");
        break;
    default:
        break;
    }
}

HeaderTableItem::DayType HeaderTableItem::getDayType() {
    return dayType_;
}

void HeaderTableItem::updateDayTypeInBase() {
    QDate weekStart = QDate::currentDate();
    if (weekStart.dayOfWeek() != 1) {
        weekStart = weekStart.addDays(-weekStart.dayOfWeek() + 1);
    }

    if (day_ != HeaderTableItem::WeekDay::None || day_ != HeaderTableItem::WeekDay::Any) {
        QSqlQuery* query = new QSqlQuery();
        query->prepare("REPLACE INTO ТипДня(Тип, День) VALUES(?, ?)");
        query->bindValue(0, static_cast<int>(dayType_));
        query->bindValue(1, weekStart.addDays(static_cast<int>(day_) - 1));
        query->exec();
        query->clear();
        delete query;
    }
}

void HeaderTableItem::setTableModel(QAbstractItemModel* model) {
    ui->tblData->setModel(model);
    QSqlTableModel* sqlModel = reinterpret_cast<QSqlTableModel*>(ui->tblData->model());
    if (type_ == HeaderTableItem::Type::Day) {
        ui->tblData->hideColumn(sqlModel->fieldIndex((QString("Описание"))));
        ui->tblData->hideColumn(sqlModel->fieldIndex((QString("Год"))));
        ui->tblData->hideColumn(sqlModel->fieldIndex((QString("Неделя"))));
        ui->lblDay->setMinimumWidth(ui->tblData->columnWidth(0) - 1);
    }
    else {
        dayVisible(false);
    }
}

QAbstractItemModel* HeaderTableItem::getTableModel() {
    return ui->tblData->model();
}

void HeaderTableItem::setType(HeaderTableItem::Type type) {
    if (type_ == HeaderTableItem::Type::None) {
        type_ = type;
        if (type_ == HeaderTableItem::Type::Day) {
            QDate weekStart = QDate::currentDate();
            if (weekStart.dayOfWeek() != 1) {
                weekStart = weekStart.addDays(-weekStart.dayOfWeek() + 1);
            }

            if (day_ != HeaderTableItem::WeekDay::None) {
                setDay(QString::number(weekStart.addDays(static_cast<int>(day_) - 1).day()));
            }
        }
    }
}

HeaderTableItem::Type HeaderTableItem::getType() {
    return type_;
}

void HeaderTableItem::setDayNum(HeaderTableItem::WeekDay day) {
    if (day_ == HeaderTableItem::WeekDay::None) {
        day_ = day;
        if (day_ == HeaderTableItem::WeekDay::Any) {
            dayVisible(false);
        }
    }
}

HeaderTableItem::WeekDay HeaderTableItem::getDayNum() {
    return day_;
}

QString HeaderTableItem::getDayDBName() {
    switch (day_) {
    case HeaderTableItem::WeekDay::None:
        return QString("");
    case HeaderTableItem::WeekDay::Monday:
        return QString("Понедельник");
    case HeaderTableItem::WeekDay::Tuesday:
        return QString("Вторник");
    case HeaderTableItem::WeekDay::Wednesday:
        return QString("Среда");
    case HeaderTableItem::WeekDay::Thursday:
        return QString("Четверг");
    case HeaderTableItem::WeekDay::Friday:
        return QString("Пятница");
    case HeaderTableItem::WeekDay::Saturday:
        return QString("Суббота");
    case HeaderTableItem::WeekDay::Sunday:
        return QString("Воскресенье");
    case HeaderTableItem::WeekDay::Any:
        return QString("Любой");
    default:
        return QString("");
    }
}

void HeaderTableItem::setWeekNum(int week) {
    weekNumber_ = week;
}

int HeaderTableItem::getWeekNum() {
    return weekNumber_;
}

void HeaderTableItem::setYearNum(int year) {
    yearNumber_ = year;
}

int HeaderTableItem::getYearNum() {
    return yearNumber_;
}

void HeaderTableItem::copySettings(HeaderTableItem* item) {
    this->type_ = Type::None;
    this->day_ = WeekDay::None;

    setType(item->getType());
    setDayNum(item->getDayNum());

    setYearNum(item->getYearNum());
    setWeekNum(item->getWeekNum());

    setTitle(item->getTitle());
    setDay(item->getDay());
    setTableModel(item->getTableModel());

    setDayType(item->getDayType());
}

int HeaderTableItem::getSelectedRow() {
    return ui->tblData->currentIndex().row();
}

void HeaderTableItem::removeSelectedRow() {
    ui->tblData->model()->removeRow(ui->tblData->currentIndex().row());
}

void HeaderTableItem::updateModel() {
    QSqlTableModel* model = reinterpret_cast<QSqlTableModel*>(ui->tblData->model());
    if (type_ == HeaderTableItem::Type::Day) {
        model->setFilter("Год = " + QString::number(getYearNum()) + " AND Неделя = " + QString::number(getWeekNum()));
    }

    model->select();
}

void HeaderTableItem::columnVisible(QString columnName, bool state) {
    QSqlTableModel* model = reinterpret_cast<QSqlTableModel*>(ui->tblData->model());
    if (state) {
        ui->tblData->showColumn(model->fieldIndex((columnName)));
    }
    else {
        ui->tblData->hideColumn(model->fieldIndex((columnName)));
    }
}

void HeaderTableItem::dayVisible(bool state) {
    ui->lblDay->setVisible(state);
    ui->lnDayHeader->setVisible(state);
}

void HeaderTableItem::configureVisible(bool state) {
    ui->btnConfigure->setVisible(state);
}

void HeaderTableItem::on_btnConfigure_clicked()
{
    btnCofifguredClicked(this);
}

