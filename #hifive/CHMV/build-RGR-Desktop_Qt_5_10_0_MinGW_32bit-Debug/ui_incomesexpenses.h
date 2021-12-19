/********************************************************************************
** Form generated from reading UI file 'incomesexpenses.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INCOMESEXPENSES_H
#define UI_INCOMESEXPENSES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_IncomesExpenses
{
public:
    QGridLayout *gridLayout_2;
    QPushButton *btnDeleteAddEdit;
    QLineEdit *lnEditRecurringPayment;
    QComboBox *cmbRecurringIncomesexpences;
    QLabel *lblEditAdd;
    QLineEdit *lnEditAddEdit;
    QComboBox *cmbAddIncomesexpences;
    QLabel *lblRecurringPayment;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *IncomesExpenses)
    {
        if (IncomesExpenses->objectName().isEmpty())
            IncomesExpenses->setObjectName(QStringLiteral("IncomesExpenses"));
        IncomesExpenses->resize(386, 167);
        IncomesExpenses->setMinimumSize(QSize(386, 167));
        IncomesExpenses->setMaximumSize(QSize(386, 167));
        gridLayout_2 = new QGridLayout(IncomesExpenses);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        btnDeleteAddEdit = new QPushButton(IncomesExpenses);
        btnDeleteAddEdit->setObjectName(QStringLiteral("btnDeleteAddEdit"));
        btnDeleteAddEdit->setMinimumSize(QSize(0, 30));
        btnDeleteAddEdit->setMaximumSize(QSize(30, 30));
        QFont font;
        font.setPointSize(12);
        btnDeleteAddEdit->setFont(font);
        btnDeleteAddEdit->setFocusPolicy(Qt::NoFocus);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/delete_black_24dp.svg"), QSize(), QIcon::Normal, QIcon::Off);
        btnDeleteAddEdit->setIcon(icon);
        btnDeleteAddEdit->setIconSize(QSize(24, 24));

        gridLayout_2->addWidget(btnDeleteAddEdit, 3, 2, 1, 1);

        lnEditRecurringPayment = new QLineEdit(IncomesExpenses);
        lnEditRecurringPayment->setObjectName(QStringLiteral("lnEditRecurringPayment"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lnEditRecurringPayment->sizePolicy().hasHeightForWidth());
        lnEditRecurringPayment->setSizePolicy(sizePolicy);
        lnEditRecurringPayment->setMinimumSize(QSize(0, 30));
        lnEditRecurringPayment->setMaximumSize(QSize(100, 16777215));
        lnEditRecurringPayment->setFont(font);
        lnEditRecurringPayment->setMaxLength(10);

        gridLayout_2->addWidget(lnEditRecurringPayment, 5, 1, 1, 1);

        cmbRecurringIncomesexpences = new QComboBox(IncomesExpenses);
        cmbRecurringIncomesexpences->setObjectName(QStringLiteral("cmbRecurringIncomesexpences"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cmbRecurringIncomesexpences->sizePolicy().hasHeightForWidth());
        cmbRecurringIncomesexpences->setSizePolicy(sizePolicy1);
        cmbRecurringIncomesexpences->setMinimumSize(QSize(220, 30));
        cmbRecurringIncomesexpences->setMaximumSize(QSize(220, 16777215));
        cmbRecurringIncomesexpences->setFont(font);
        cmbRecurringIncomesexpences->setEditable(false);

        gridLayout_2->addWidget(cmbRecurringIncomesexpences, 5, 0, 1, 1);

        lblEditAdd = new QLabel(IncomesExpenses);
        lblEditAdd->setObjectName(QStringLiteral("lblEditAdd"));
        lblEditAdd->setFont(font);

        gridLayout_2->addWidget(lblEditAdd, 0, 0, 1, 4);

        lnEditAddEdit = new QLineEdit(IncomesExpenses);
        lnEditAddEdit->setObjectName(QStringLiteral("lnEditAddEdit"));
        sizePolicy.setHeightForWidth(lnEditAddEdit->sizePolicy().hasHeightForWidth());
        lnEditAddEdit->setSizePolicy(sizePolicy);
        lnEditAddEdit->setMinimumSize(QSize(0, 30));
        lnEditAddEdit->setMaximumSize(QSize(100, 16777215));
        lnEditAddEdit->setFont(font);
        lnEditAddEdit->setMaxLength(10);

        gridLayout_2->addWidget(lnEditAddEdit, 3, 1, 1, 1);

        cmbAddIncomesexpences = new QComboBox(IncomesExpenses);
        cmbAddIncomesexpences->setObjectName(QStringLiteral("cmbAddIncomesexpences"));
        sizePolicy1.setHeightForWidth(cmbAddIncomesexpences->sizePolicy().hasHeightForWidth());
        cmbAddIncomesexpences->setSizePolicy(sizePolicy1);
        cmbAddIncomesexpences->setMinimumSize(QSize(220, 30));
        cmbAddIncomesexpences->setMaximumSize(QSize(220, 16777215));
        cmbAddIncomesexpences->setFont(font);
        cmbAddIncomesexpences->setEditable(true);

        gridLayout_2->addWidget(cmbAddIncomesexpences, 3, 0, 1, 1);

        lblRecurringPayment = new QLabel(IncomesExpenses);
        lblRecurringPayment->setObjectName(QStringLiteral("lblRecurringPayment"));
        lblRecurringPayment->setFont(font);

        gridLayout_2->addWidget(lblRecurringPayment, 4, 0, 1, 1);

        buttonBox = new QDialogButtonBox(IncomesExpenses);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setFont(font);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);
        buttonBox->setCenterButtons(true);

        gridLayout_2->addWidget(buttonBox, 7, 0, 1, 3);


        retranslateUi(IncomesExpenses);
        QObject::connect(buttonBox, SIGNAL(accepted()), IncomesExpenses, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), IncomesExpenses, SLOT(reject()));

        QMetaObject::connectSlotsByName(IncomesExpenses);
    } // setupUi

    void retranslateUi(QDialog *IncomesExpenses)
    {
        btnDeleteAddEdit->setText(QString());
        lblEditAdd->setText(QApplication::translate("IncomesExpenses", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 / \320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        lblRecurringPayment->setText(QApplication::translate("IncomesExpenses", "\320\237\320\276\320\262\321\202\320\276\321\200\321\217\321\216\321\211\320\270\320\271\321\201\321\217 \320\277\320\273\320\260\321\202\321\221\320\266", nullptr));
        Q_UNUSED(IncomesExpenses);
    } // retranslateUi

};

namespace Ui {
    class IncomesExpenses: public Ui_IncomesExpenses {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INCOMESEXPENSES_H
