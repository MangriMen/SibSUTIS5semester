#include "adddialog.h"
#include "ui_adddialog.h"

AddDialog::AddDialog(QWidget *parent, HeaderTableItem::Type type) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags().setFlag(Qt::WindowContextHelpButtonHint, false));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(checkAccepted()));

    comboBoxSavedStyle = ui->cmbTask->styleSheet();
    type_ = type;

    ui->dtTime->setDateTime(QDateTime::currentDateTime());

    switch (type) {
    case HeaderTableItem::Type::Day:
        ui->dtTime->setDisplayFormat("HH:mm");
    {
        QStringList tasks;
        QSqlQuery* query = new QSqlQuery();
        query->prepare("SELECT Задание FROM Учебные");
        query->exec();
        while (query->next()) {
            tasks.append(query->value(0).value<QString>());
        }
        query->clear();
        int sep1 = tasks.count();
        query->prepare("SELECT Задание FROM Рабочие");
        query->exec();
        while (query->next()) {
            tasks.append(query->value(0).value<QString>());
        }
        query->clear();
        int sep2 = tasks.count();
        query->prepare("SELECT Задание FROM Личные");
        query->exec();
        while (query->next()) {
            tasks.append(query->value(0).value<QString>());
        }
        query->clear();
        int sep3 = tasks.count();
        query->prepare("SELECT Задание FROM Место");
        query->exec();
        while (query->next()) {
            tasks.append(query->value(0).value<QString>());
        }
        query->clear();
        int sep4 = tasks.count();
        delete query;
        ui->cmbTask->addItems(tasks);

        if (sep1) {
            ui->cmbTask->insertSeparator(sep1);
        }

        if (sep2) {
            ui->cmbTask->insertSeparator(sep2);
        }

        if (sep3) {
            ui->cmbTask->insertSeparator(sep3);
        }

        if (sep4) {
            ui->cmbTask->insertSeparator(sep4);
        }
    }
        count = 3;
        break;
    case HeaderTableItem::Type::Education:
        ui->lblTask->setText("Предмет");
        ui->lblDescription->setText("Задание");
        ui->lblTime->setText("Срок сдачи");
        count = 3;
        hideComboBoxArrow(true);
        break;
    case HeaderTableItem::Type::Work:
        ui->lblTask->setText("Задание");
        ui->lblTime->setText("Срок сдачи");
        count = 2;
        ui->pteDescription->setVisible(false);
        ui->lblDescription->setVisible(false);
        hideComboBoxArrow(true);
        adjustSize();
        break;
    case HeaderTableItem::Type::Personal:
        ui->lblTask->setText("Задание");
        count = 1;
        ui->pteDescription->setVisible(false);
        ui->lblDescription->setVisible(false);
        ui->dtTime->setVisible(false);
        ui->lblTime->setVisible(false);
        hideComboBoxArrow(true);
        adjustSize();
        break;
    case HeaderTableItem::Type::Places:
        ui->lblTask->setText("Задание");
        count = 1;
        ui->pteDescription->setVisible(false);
        ui->lblDescription->setVisible(false);
        ui->dtTime->setVisible(false);
        ui->lblTime->setVisible(false);
        hideComboBoxArrow(true);
        adjustSize();
        break;
    default:
        break;
    }
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::setTask(QString task) {
    ui->cmbTask->setCurrentText(task);
}

QString AddDialog::getTask() {
    return ui->cmbTask->currentText().trimmed();
}

void AddDialog::setDescription(QString description) {
    ui->pteDescription->setPlainText(description);
}

QString AddDialog::getDescription() {
    return ui->pteDescription->toPlainText().trimmed();
}

void AddDialog::setTime(QDateTime time) {
    ui->dtTime->setDateTime(time);
}

QDateTime AddDialog::getTime() {
    return ui->dtTime->dateTime();
}

int AddDialog::getFieldCount() {
    return count;
}

void AddDialog::checkAccepted() {
    if (ui->cmbTask->currentText().trimmed().isEmpty()) {
        QMessageBox::information(this, tr("Not all fields are filled"), tr("Fields must not be empty"));
        return;
    }
    if (type_ == HeaderTableItem::Type::Education) {
        if (ui->pteDescription->toPlainText().trimmed().isEmpty()) {
            QMessageBox::information(this, tr("Not all fields are filled"), tr("Fields must not be empty"));
            return;
        }
    }
    if (ui->dtTime->isVisible()) {
        if(ui->dtTime->dateTime() < QDateTime::currentDateTime()) {
            QMessageBox::information(this, tr("Not all fields are filled"), tr("Date cannot be set earlier than today"));
            return;
        }
    }

    accept();
}

void AddDialog::hideComboBoxArrow(bool state) {
    if (state) {
        ui->cmbTask->setStyleSheet("QComboBox::drop-down {width: 0px; border-left-width: 0px;}");
    }
    else {
        ui->cmbTask->setStyleSheet(comboBoxSavedStyle);
    }
}
