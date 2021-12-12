#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
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
