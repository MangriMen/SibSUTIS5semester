#include "lyovkin_panin.h"
#include "ui_lyovkin_panin.h"
#include <QTextDocumentWriter>
#include <QFileDialog>
#include <QMessageBox>

Lyovkin_Panin::Lyovkin_Panin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Lyovkin_Panin)
{
    ui->setupUi(this);
}

Lyovkin_Panin::~Lyovkin_Panin()
{
    delete ui;
}

void Lyovkin_Panin::recieveData(QString str)
{
    QStringList lst = str.split("*");
    ui->textEdit->setText(lst.at(1) + "\n" + lst.at(0));

    if (lst.size() > 1) {
        QImage photo(lst.at(0));
        if (photo.isNull()){
            return;
        }
        QPixmap photoPixmap(QPixmap::fromImage(photo).scaled(ui->label->width(), ui->label->maximumHeight(), Qt::KeepAspectRatio));
        ui->label->setPixmap(photoPixmap);
        ui->label->resize(photoPixmap.width(), photoPixmap.height());
    }
}

void Lyovkin_Panin::on_buttonBox_clicked(QAbstractButton *button)
{
    if (button->text() == "Reset") {
        ui->textEdit->clear();
        ui->label->clear();
    }
    else if (button->text() == "Save") {
        QString fileName = QFileDialog::getSaveFileName(0, "Сохранить файл", QDir::currentPath(), "*.txt");
        QTextDocumentWriter writer;
        writer.setFileName(fileName);
        writer.write(ui->textEdit->document());
    }
    else if (button->text() == "Open") {
        QString fileName = QFileDialog::getOpenFileName(0, "Открыть файл", QDir::currentPath(), "*.txt");
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            ui->textEdit->setPlainText(file.readAll());
            QStringList lst = ui->textEdit->toPlainText().split("\n");
            QImage photo(lst.at(5));
            if (photo.isNull()){
                return;
            }
            QPixmap photoPixmap(QPixmap::fromImage(photo).scaled(ui->label->width(), ui->label->maximumHeight(), Qt::KeepAspectRatio));
            ui->label->setPixmap(photoPixmap);
            ui->label->resize(photoPixmap.width(), photoPixmap.height());
        }
    }
}
