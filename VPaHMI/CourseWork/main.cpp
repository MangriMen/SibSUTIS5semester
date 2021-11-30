#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QMessageBox>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString defualtTranslation = QLatin1String("qt_") + QLocale::system().name();
    QTranslator *translatorDefault = new QTranslator();
    if (translatorDefault->load(defualtTranslation, QLibraryInfo::location(QLibraryInfo::TranslationsPath))) {
        qApp->installTranslator(translatorDefault);
    }
    else {
        QMessageBox::warning(0, "Error when loading translation", "There was an error loading the default translation\"" + QLocale::system().name() + "\"");
    }

    QString customTranslation = QLatin1String("QtLanguage_") + QLatin1String("ru_RU");
    QTranslator *translatorCustom = new QTranslator();
    if (translatorCustom->load(customTranslation, QString(":/translations/"))) {
        qApp->installTranslator(translatorCustom);
    }
    else {
        QMessageBox::warning(0, "Error when loading translation", "There was an error loading the translation \"" + customTranslation + "\"");
    }

    MainWindow w;
    w.show();

    return a.exec();
}
