#ifndef STARTDIALOG_LYOVKIN_PANIN_H
#define STARTDIALOG_LYOVKIN_PANIN_H
#include <QPushButton>
#include <QMessageBox>
#include "InputDialog.h"

class StartDialog_Lyovkin_Panin : public QPushButton
{
    Q_OBJECT
public:
    StartDialog_Lyovkin_Panin(QWidget* pwgt = 0): QPushButton("Нажми", pwgt)
    {
        connect(this, SIGNAL(clicked()), SLOT(slotButtonClicked()));
    }

private slots:
    void slotButtonClicked()
    {
        InputDialog* pInputDialog = new InputDialog;
        if (pInputDialog->exec() == QDialog::Accepted) {
            if (
                (pInputDialog->firstName().toLower() == "игорь" && pInputDialog->lastName().toLower() == "лёвкин")
                ||
                (pInputDialog->firstName().toLower() == "никита" && pInputDialog->lastName().toLower() == "панин")
               ) {
            QMessageBox::information(
                        0,
                        "Ваша информация",
                        "Имя: "
                        + pInputDialog->firstName()
                        + "\nФамилия: "
                        + pInputDialog->lastName()
                        );
            }
        }
        delete pInputDialog;
    }
};

#endif // STARTDIALOG_LYOVKIN_PANIN_H
