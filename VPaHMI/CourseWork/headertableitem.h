#ifndef HEADERTABLEITEM_H
#define HEADERTABLEITEM_H

#include <QWidget>

namespace Ui {
class HeaderTableItem;
}

class HeaderTableItem : public QWidget
{
    Q_OBJECT

public:
    explicit HeaderTableItem(QWidget *parent = 0);
    ~HeaderTableItem();

private:
    Ui::HeaderTableItem *ui;
};

#endif // HEADERTABLEITEM_H
