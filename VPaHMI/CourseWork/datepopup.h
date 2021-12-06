#ifndef DATEPOPUP_H_
#define DATEPOPUP_H_

#include <QDialog>
#include <QDate>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QCalendarWidget>

class DatePopup : public QDialog{
    Q_OBJECT
public:
    DatePopup(QWidget *parent=0);
    QDate selectedDate() const;

private:
    QWidget *widget;
    QCalendarWidget *calendarWidget;
    QDialogButtonBox* buttonBox;
    QGridLayout *gridLayout;

};

#endif /* DATEPOPUP_H */
