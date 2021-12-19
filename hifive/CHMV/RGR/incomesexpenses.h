#ifndef INCOMESEXPENSES_H
#define INCOMESEXPENSES_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class IncomesExpenses;
}

class IncomesExpenses : public QDialog
{
    Q_OBJECT

public:
    explicit IncomesExpenses(QSqlTableModel *tableModel, QString title, QWidget *parent = 0);
    QSqlTableModel *incomesExpensesModel = nullptr;
    QString windowTitle = "ДоходыРасходы";
    ~IncomesExpenses();

public slots:
    void onGuiUpdate();
    void onAddEditCmbChanged(QString item);
    void onRecurringCmbChanged(QString item);
    void onAddIncomesexpencesChanged(QString payment);
    void onRecurringChanged(QString payment);
    void onItemRemove();

private:
    Ui::IncomesExpenses *ui;
};

#endif // INCOMESEXPENSES_H
