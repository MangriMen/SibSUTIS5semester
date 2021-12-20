#ifndef GOALS_H
#define GOALS_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class Goals;
}

class Goals : public QDialog
{
    Q_OBJECT

public:
    explicit Goals(QSqlTableModel *modelGoals, QSqlTableModel *modelFunds, QWidget *parent = 0);
    QSqlTableModel* goalsModel = nullptr;
    QSqlTableModel* fundsModel = nullptr;
    ~Goals();

signals:
    void GoalBalanceModified(int diff, int index);

private slots:
    void onGuiUpdate();

    void onAddGoalIndexChanged(QString item);

    void onGoalPriceChanged(QString item);

    void onGoalImageChanged();

    void onItemRemove();

    void on_btnTransferAccept_clicked();

    void on_btnWithdrawAccept_clicked();

    void on_btnMakeCurrent_clicked();

    void on_btnDiscardGoal_clicked();

private:
    Ui::Goals *ui;

};

#endif // GOALS_H
