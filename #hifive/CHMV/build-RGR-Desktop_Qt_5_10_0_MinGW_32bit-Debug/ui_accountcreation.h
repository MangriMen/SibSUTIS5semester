/********************************************************************************
** Form generated from reading UI file 'accountcreation.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACCOUNTCREATION_H
#define UI_ACCOUNTCREATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_accountCreation
{
public:
    QGridLayout *gridLayout;
    QLabel *lblAddNewAccount;
    QDialogButtonBox *buttonBox;
    QLineEdit *lnEditAccountName;

    void setupUi(QDialog *accountCreation)
    {
        if (accountCreation->objectName().isEmpty())
            accountCreation->setObjectName(QStringLiteral("accountCreation"));
        accountCreation->resize(276, 101);
        accountCreation->setMinimumSize(QSize(276, 101));
        accountCreation->setMaximumSize(QSize(276, 101));
        gridLayout = new QGridLayout(accountCreation);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lblAddNewAccount = new QLabel(accountCreation);
        lblAddNewAccount->setObjectName(QStringLiteral("lblAddNewAccount"));
        QFont font;
        font.setPointSize(12);
        lblAddNewAccount->setFont(font);

        gridLayout->addWidget(lblAddNewAccount, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(accountCreation);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setFont(font);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);

        gridLayout->addWidget(buttonBox, 3, 0, 1, 1);

        lnEditAccountName = new QLineEdit(accountCreation);
        lnEditAccountName->setObjectName(QStringLiteral("lnEditAccountName"));
        lnEditAccountName->setFont(font);

        gridLayout->addWidget(lnEditAccountName, 1, 0, 1, 1);


        retranslateUi(accountCreation);
        QObject::connect(buttonBox, SIGNAL(rejected()), accountCreation, SLOT(reject()));

        QMetaObject::connectSlotsByName(accountCreation);
    } // setupUi

    void retranslateUi(QDialog *accountCreation)
    {
        accountCreation->setWindowTitle(QApplication::translate("accountCreation", "\320\235\320\276\320\262\321\213\320\271 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\214", nullptr));
        lblAddNewAccount->setText(QApplication::translate("accountCreation", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\270\320\274\321\217 \320\275\320\276\320\262\320\276\320\263\320\276 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class accountCreation: public Ui_accountCreation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCOUNTCREATION_H
