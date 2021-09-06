#include "startdialog_lyovkin_panin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartDialog_Lyovkin_Panin startDialog;
    startDialog.show();

    return a.exec();
}
