#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile styleFile(":/style.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleString = QLatin1String(styleFile.readAll());
        qApp->setStyleSheet(styleString);
    }

    myForm = new Lyovkin_Panin();
    connect(ui->pbUploadPhoto, SIGNAL(clicked()), this, SLOT(loadPhoto()));
    connect(ui->pbDone, SIGNAL(clicked()), this, SLOT(generateAndSendData()));
    connect(this, SIGNAL(sendData(QString)), myForm, SLOT(show()));
    connect(this, SIGNAL(sendData(QString)), myForm, SLOT(recieveData(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateAndSendData()
{
    if (ui->lePhotoPath->text() == ""
        || ui->leFullName->text() == ""
        || ui->lePost->text() == ""
        || ui->leCitizenShip->text() == ""
        || ui->deDateOfBirth->text() == ""
        || (!ui->rbMale->isChecked() && !ui->rbFemale->isChecked())) {
        QMessageBox::warning(0, "Незаполненные поля", "Для продолжения все поля должны быть заполнены!");
        return;
    }

    QString str = ui->lePhotoPath->text()
            + "*"
            + ui->lblFullName->text() + ": " + ui->leFullName->text()
            + "\n"
            + ui->lblPost->text() + ": " +ui->lePost->text()
            + "\n"
            + ui->lblCitizenShip->text() + ": " +ui->leCitizenShip->text()
            + "\n"
            + ui->lblDateOfBirth->text() + ": " +ui->deDateOfBirth->text()
            + "\n"
            + "Пол: ";
    if (ui->rbMale->isChecked()) {
        str += "мужской";
    } else {
        str += "женский";
    }

    emit sendData(str);
}

void MainWindow::loadPhoto()
{
    QString filename = QFileDialog::getOpenFileName(
                0,
                "Выберите изображение",
                QDir::currentPath(),
                "*.png *.jpg *.jpeg *.gif"
                );
    QImage photo(filename);
    if (photo.isNull()){
        return;
    }
    ui->lePhotoPath->setText(filename);
    ui->lePhotoPath->setToolTip(filename);
    QPixmap photoPixmap = QPixmap::fromImage(photo).scaled(ui->lblPhoto->width(), ui->lblPhoto->maximumHeight(), Qt::KeepAspectRatio);
    ui->lblPhoto->setPixmap(photoPixmap);
    ui->lblPhoto->resize(photoPixmap.width(), photoPixmap.height());
}

