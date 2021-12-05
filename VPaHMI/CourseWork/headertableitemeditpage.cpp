#include "headertableitemeditpage.h"
#include "ui_headertableitemeditpage.h"
#include "adddialog.h"

HeaderTableItemEditPage::HeaderTableItemEditPage(QWidget *parent, HeaderTableItem* item) :
    QWidget(parent),
    ui(new Ui::HeaderTableItemEditPage)
{
    ui->setupUi(this);

    this->item_ = item;

    int rowInsert = 0;
    ui->layoutPage->addWidget(ui->btnBack, rowInsert++, 0);
    ui->layoutPage->addWidget(ui->btnSave, rowInsert++, 0);
    if (item_->getType() == HeaderTableItem::Type::Day) {
        if (item->getDayNum() != HeaderTableItem::WeekDay::Any) {
            cmbDayType = new WideComboBox(this);
            cmbDayType->addItem(QString("Учебный"), static_cast<int>(HeaderTableItem::DayType::Education));
            cmbDayType->addItem(QString("Рабочий"), static_cast<int>(HeaderTableItem::DayType::Work));
            cmbDayType->addItem(QString("Смешанный"), static_cast<int>(HeaderTableItem::DayType::EducationAndWork));
            cmbDayType->addItem(QString("Выходной"), static_cast<int>(HeaderTableItem::DayType::DayOff));
            cmbDayType->setMaximumSize(ui->btnBack->maximumSize());
            cmbDayType->setCurrentIndex(static_cast<int>(item_->getDayType()));
            cmbDayType->setFont(QFont("Roboto", 12));
            cmbDayType->setStyleSheet("QComboBox {padding: 30px;} QComboBox::drop-down {background-color: transparent; width: 44%;} QComboBox::down-arrow {image: url(:/images/arrow_down.png);}");
            connect(cmbDayType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_dayTypeSelected(int)));
            ui->layoutPage->addWidget(cmbDayType, rowInsert++, 0);
        }
    }
    ui->layoutPage->addItem(ui->verticalSpacer, rowInsert++, 0);
    ui->layoutPage->addWidget(ui->btnAdd, rowInsert++, 0);
    ui->layoutPage->addWidget(ui->btnEdit, rowInsert++, 0);
    ui->layoutPage->addWidget(ui->btnRemove, rowInsert++, 0);
    ui->layoutPage->addWidget(ui->hitEditingItem, 0, 1, -1, -1);

    ui->hitEditingItem->copySettings(item);
    ui->hitEditingItem->configureVisible(false);
    ui->hitEditingItem->updateModel();
    ui->hitEditingItem->columnVisible(QString("Описание"), true);
}

HeaderTableItemEditPage::~HeaderTableItemEditPage()
{
    ui->layoutPage->removeWidget(ui->btnBack);
    ui->layoutPage->removeWidget(ui->btnSave);
    if (cmbDayType != nullptr) {
        ui->layoutPage->removeWidget(cmbDayType);
    }
    ui->layoutPage->removeItem(ui->verticalSpacer);
    ui->layoutPage->removeWidget(ui->btnAdd);
    ui->layoutPage->removeWidget(ui->btnEdit);
    ui->layoutPage->removeWidget(ui->btnRemove);
    ui->layoutPage->removeWidget(ui->hitEditingItem);
    delete ui;
}

void HeaderTableItemEditPage::on_btnAdd_clicked()
{
    AddDialog* dlg = new AddDialog(this, item_->getType());
    dlg->setWindowTitle(tr("Add task"));
    dlg->exec();

    if (dlg->result() == QDialog::Accepted) {
        QString tableName = reinterpret_cast<QSqlTableModel*>(item_->getTableModel())->tableName();

        const QString insertQueryStr = QString("INSERT INTO ") + tableName + QString(" VALUES (");
        const QString insertQueryStrEnd = QString(");");
        const QString valueStr = QString("?, ");

        QString values;
        if (item_->getType() == HeaderTableItem::Type::Day) {
            values.append(valueStr);
            values.append(valueStr);
        }
        for (int i = 0; i < dlg->getFieldCount(); i++) {
            values.append(valueStr);
        }
        values.remove(values.count()-2, 1);

        QSqlQuery* addQuery = new QSqlQuery();
        addQuery->prepare(insertQueryStr + values + insertQueryStrEnd);
        switch (item_->getType()) {
        case HeaderTableItem::Type::Day:
            addQuery->bindValue(0, dlg->getTime().time().toString("hh:mm"));
            addQuery->bindValue(1, dlg->getTask());
            addQuery->bindValue(2, dlg->getDescription());
            addQuery->bindValue(3, item_->getYearNum());
            addQuery->bindValue(4, item_->getWeekNum());
            break;
        case HeaderTableItem::Type::Education:
            addQuery->bindValue(0, dlg->getTask());
            addQuery->bindValue(1, dlg->getDescription());
            addQuery->bindValue(2, dlg->getTime().toString("dd.MM.yyyy HH:mm"));
            break;
        case HeaderTableItem::Type::Work:
            addQuery->bindValue(0, dlg->getTask());
            addQuery->bindValue(1, dlg->getTime().toString("dd.MM.yyyy HH:mm"));
            break;
        case HeaderTableItem::Type::Personal:
            addQuery->bindValue(0, dlg->getTask());
            break;
        case HeaderTableItem::Type::Places:
            addQuery->bindValue(0, dlg->getTask());
            break;
        default:
            break;
        }
        addQuery->exec();
        addQuery->clear();
        delete addQuery;

        item_->updateModel();
    }
}

void HeaderTableItemEditPage::on_btnBack_clicked()
{
    btnBackClicked();
}

void HeaderTableItemEditPage::on_btnEdit_clicked()
{
    QSqlTableModel* model = reinterpret_cast<QSqlTableModel*>(item_->getTableModel());

    AddDialog* dlg = new AddDialog(this, item_->getType());
    dlg->setWindowTitle(tr("Edit task"));
    dlg->exec();
    switch (item_->getType()) {
    case HeaderTableItem::Type::Day:
        model->setData(model->index(ui->hitEditingItem->getSelectedRow(), 0), dlg->getTime().time().toString("hh:mm"));
        model->setData(model->index(ui->hitEditingItem->getSelectedRow(), 1), dlg->getTask());
        model->setData(model->index(ui->hitEditingItem->getSelectedRow(), 2), dlg->getDescription());
        break;
    case HeaderTableItem::Type::Education:
        model->setData(model->index(ui->hitEditingItem->getSelectedRow(), 0), dlg->getTask());
        model->setData(model->index(ui->hitEditingItem->getSelectedRow(), 1), dlg->getDescription());
        model->setData(model->index(ui->hitEditingItem->getSelectedRow(), 2), dlg->getTime().toString("dd.MM.yyyy HH:mm"));
        break;
    case HeaderTableItem::Type::Work:
        model->setData(model->index(ui->hitEditingItem->getSelectedRow(), 0), dlg->getTask());
        model->setData(model->index(ui->hitEditingItem->getSelectedRow(), 1), dlg->getTime().toString("dd.MM.yyyy HH:mm"));
        break;
    case HeaderTableItem::Type::Personal:
        model->setData(model->index(ui->hitEditingItem->getSelectedRow(), 0), dlg->getTask());
        break;
    case HeaderTableItem::Type::Places:
        model->setData(model->index(ui->hitEditingItem->getSelectedRow(), 0), dlg->getTask());
        break;
    default:
        break;
    }
    item_->updateModel();
}

void HeaderTableItemEditPage::on_btnRemove_clicked()
{
    ui->hitEditingItem->removeSelectedRow();
    item_->updateModel();
}

void HeaderTableItemEditPage::on_dayTypeSelected(int index) {
    HeaderTableItem::DayType newType = static_cast<HeaderTableItem::DayType>(cmbDayType->itemData(index).value<int>());
    ui->hitEditingItem->setDayType(newType);
    item_->setDayType(newType);
    item_->updateDayTypeInBase();
}
