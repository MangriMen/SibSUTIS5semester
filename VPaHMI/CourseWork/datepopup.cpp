#include "datepopup.h"

DatePopup::DatePopup(QWidget *parent)
:QDialog(parent, Qt::Popup)
{
    QFont font("Roboto", 12);
    setFont(font);

    setSizeGripEnabled(false);
    this->setObjectName(QString::fromUtf8("datePopup"));
    setStyleSheet("QCalendarWidget QTableView {border-radius: 4px;} #datePopup, QDialogButtonBox {border-radius: 4px;}");

    gridLayout = new QGridLayout(this);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    gridLayout->setContentsMargins(0, 0, 0, gridLayout->contentsMargins().bottom() / 2);

    calendarWidget = new QCalendarWidget(this);
    calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));
    calendarWidget->setFont(font);
    calendarWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    calendarWidget->setMinimumHeight(193);

    gridLayout->addWidget(calendarWidget, 0, 0);

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    buttonBox->setFont(font);
    buttonBox->setCenterButtons(true);

    gridLayout->addWidget(buttonBox, 1, 0);

    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

QDate DatePopup::selectedDate() const{
    return calendarWidget->selectedDate();
}
