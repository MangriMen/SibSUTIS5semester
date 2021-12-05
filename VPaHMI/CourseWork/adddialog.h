#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QStringList>
#include "headertableitem.h"

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

private:
    HeaderTableItem::Type type_;

public:
    explicit AddDialog(QWidget *parent = 0, HeaderTableItem::Type type = HeaderTableItem::Type::Places);
    ~AddDialog();

    void setTask(QString task);
    QString getTask();

    void setDescription(QString description);
    QString getDescription();

    void setTime(QDateTime time);
    QDateTime getTime();

    int count;

    int getFieldCount();

public slots:
    void checkAccepted();

private:
    QString comboBoxSavedStyle;
    void hideComboBoxArrow(bool state);

    Ui::AddDialog *ui;
};

#endif // ADDDIALOG_H
