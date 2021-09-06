#ifndef LYOVKIN_PANIN_H
#define LYOVKIN_PANIN_H

#include <QWidget>
#include <QAbstractButton>

namespace Ui {
class Lyovkin_Panin;
}

class Lyovkin_Panin : public QWidget
{
    Q_OBJECT

public:
    explicit Lyovkin_Panin(QWidget *parent = 0);
    ~Lyovkin_Panin();

private:
    Ui::Lyovkin_Panin *ui;
public slots:
    void recieveData(QString str);
private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
};

#endif // LYOVKIN_PANIN_H
