#ifndef HEADERTABLEITEMEDITPAGE_H
#define HEADERTABLEITEMEDITPAGE_H

#include <QWidget>

namespace Ui {
class HeaderTableItemEditPage;
}

class HeaderTableItemEditPage : public QWidget
{
    Q_OBJECT

public:
    explicit HeaderTableItemEditPage(QWidget *parent = 0);
    ~HeaderTableItemEditPage();

private slots:
    void on_btnAdd_clicked();

private:
    Ui::HeaderTableItemEditPage *ui;
};

#endif // HEADERTABLEITEMEDITPAGE_H
