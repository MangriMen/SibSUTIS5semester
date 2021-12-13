#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDataBase>
#include <QSqlTableModel>
#include <QSqlQuery>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void guiUpdate();

private:
    Ui::MainWindow *ui;
    QSqlTableModel *modelUsers;
    QSqlTableModel *modelFunds;
    QSqlTableModel *modelGoals;
    QString currentUserName;
    QString latinize(QString str);

private slots:
    void onGuiUpdate();

    void openGoalsDialog();
    void openFundsDialog();
    void openIncomesDialog();
    void openExpencesDialog();

    void onGoalBalanceModified();

    void onAddToBankAccepted();
    void onWithdrawFromBankAccepted();
    void onRecurringPaymentAccepted();
};

#endif // MAINWINDOW_H
