#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QMessageBox>
#include <QLibraryInfo>

void initializeTranslator(QString translation, QString directory = QString("")) {
    QTranslator *translator = new QTranslator(qApp);
    bool isSuccess = false;

    if (directory.isEmpty()) {
        isSuccess = translator->load(translation);
    }
    else {
        isSuccess = translator->load(translation, directory);
    }

    if (isSuccess) {
        qApp->installTranslator(translator);
    }
    else {
        QMessageBox::warning(0, "Error when loading translation", "There was an error loading the default translation\"" + QLocale::system().name() + "\"");
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    initializeTranslator(QLatin1String("qt_") + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    initializeTranslator(QString("QtLanguage_") + QString("ru_RU"), QString(":/translations/"));

    MainWindow w;
    w.show();

    return a.exec();
}
