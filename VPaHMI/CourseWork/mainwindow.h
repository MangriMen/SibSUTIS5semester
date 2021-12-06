#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QDate>
#include <QGridLayout>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QCalendarWidget>
#include <QFile>
#include <QDate>
#include "adddialog.h"
#include "headertableitem.h"
#include "headertableitemeditpage.h"
#include "datepopup.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QWidget* savedTab;
    QSqlDatabase affairsBase;
    QSqlTableModel* educationModel;
    QSqlTableModel* workModel;
    QSqlTableModel* personalModel;
    QSqlTableModel* placesModel;
    QDate currentWeek;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setCurrentWeek(QDate date);

private slots:
    void onHelpRequested();
    void onConfigurePageRequested(HeaderTableItem* item);
    void onRestoreNavigationRequested();
    void onWeekChangeRequested();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
