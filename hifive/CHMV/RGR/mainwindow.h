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
    void incomesExpensesGuiUpdate();

private:
    Ui::MainWindow *ui;
    QSqlTableModel *modelUsers = nullptr;
    QSqlTableModel *modelFunds = nullptr;
    QSqlTableModel *modelGoals = nullptr;
    QSqlTableModel *modelIncomes = nullptr;
    QSqlTableModel *modelExpenses = nullptr;
    QString latinize(QString str);
    bool loadUsers();
    bool onUserDeleteRequested();
    void closeDatabase();
    const QString currentUserName();
    void setCurrentUserName(QString userName);

private slots:
    void onGuiUpdate();
    void onUserChanged(QAction* selectedUser);

    void openGoalsDialog();
    void openFundsDialog();
    void openIncomesDialog();
    void openExpencesDialog();

    void onGoalBalanceModified();

    void onAddToWalletAccepted(int number);
    void onAddToBankAccepted(int number);
    void onWithdrawFromBankAccepted(int number);
    void onRecurringPaymentAccepted(int number);

    bool onNewUserRequested();
};

#endif // MAINWINDOW_H
