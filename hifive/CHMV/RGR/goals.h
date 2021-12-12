#ifndef GOALS_H
#define GOALS_H

#include <QDialog>

namespace Ui {
class Goals;
}

class Goals : public QDialog
{
    Q_OBJECT

public:
    explicit Goals(QWidget *parent = 0);
    ~Goals();

signals:
    void GoalBalanceModified();

private slots:
    void on_btnTransferAccept_clicked();

    void on_btnWithdrawAccept_clicked();

private:
    Ui::Goals *ui;

};

#endif // GOALS_H
