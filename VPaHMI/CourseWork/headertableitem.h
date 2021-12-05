#ifndef HEADERTABLEITEM_H
#define HEADERTABLEITEM_H

#include <QWidget>
#include <QTabBar>
#include <QDebug>
#include <QAbstractItemModel>
#include <QDialog>
#include <QBoxLayout>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDate>

namespace Ui {
class HeaderTableItem;
}

class HeaderTableItem : public QWidget
{
    Q_OBJECT

public:
    enum class Type {
        None,
        Day,
        Education,
        Work,
        Personal,
        Places
    };

    enum class WeekDay {
        None,
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday,
        Any
    };

    enum class DayType {
        Education,
        Work,
        EducationAndWork,
        DayOff
    };

private:
    HeaderTableItem::Type type_ = HeaderTableItem::Type::None;
    HeaderTableItem::WeekDay day_ = HeaderTableItem::WeekDay::None;
    HeaderTableItem::DayType dayType_ = HeaderTableItem::DayType::DayOff;
    int weekNumber_ = 0;
    int yearNumber_ = 0;

public:
    explicit HeaderTableItem(QWidget *parent = 0);
    ~HeaderTableItem();

    void setTitle(QString title);
    QString getTitle();

    void setDay(QString title);
    QString getDay();

    void setTableModel(QAbstractItemModel* model);
    QAbstractItemModel* getTableModel();

    void setType(HeaderTableItem::Type type);
    Type getType();

    void setDayType(HeaderTableItem::DayType type);
    DayType getDayType();
    void updateDayTypeInBase();

    void setDayNum(HeaderTableItem::WeekDay day);
    WeekDay getDayNum();
    QString getDayDBName();

    void setWeekNum(int week);
    int getWeekNum();

    void setYearNum(int year);
    int getYearNum();

    void copySettings(HeaderTableItem* item);


    int getSelectedRow();
    void removeSelectedRow();
    void updateModel();

    void columnVisible(QString columnName, bool state);
    void dayVisible(bool state);
    void configureVisible(bool state);

signals:
    void btnCofifguredClicked(HeaderTableItem* item);

private slots:
    void on_btnConfigure_clicked();

private:
    Ui::HeaderTableItem *ui;
};

#endif // HEADERTABLEITEM_H
