#include "mainwindow.h"
#include <QApplication>
#include <QFile>

void loadStylesheet(QString filename) {
    QFile file(filename);
    file.open(QFile::ReadOnly);
    qApp->setStyleSheet(qApp->styleSheet() + file.readAll());
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    loadStylesheet("./style.css");

    w.show();

    return a.exec();
}
