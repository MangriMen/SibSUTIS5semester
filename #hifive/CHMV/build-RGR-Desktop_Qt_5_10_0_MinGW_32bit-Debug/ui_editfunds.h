/********************************************************************************
** Form generated from reading UI file 'editfunds.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITFUNDS_H
#define UI_EDITFUNDS_H

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
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EditFunds
{
public:
    QGridLayout *gridLayout;
    QDialogButtonBox *buttonBox;
    QGridLayout *widEditFunds;
    QPushButton *btnAddToWallet;
    QLineEdit *lnEditWithdraw;
    QPushButton *btnAddToBank;
    QLineEdit *lnEditAddToBank;
    QPushButton *btnRecurringPayment;
    QLineEdit *lnEditRecurringPayment;
    QLabel *lblRecurringPayment;
    QLabel *lblAddToBank;
    QLabel *lblWithdraw;
    QPushButton *btnWithdraw;
    QLineEdit *lnEditAddToWallet;
    QLabel *lblAddToWallet;

    void setupUi(QDialog *EditFunds)
    {
        if (EditFunds->objectName().isEmpty())
            EditFunds->setObjectName(QStringLiteral("EditFunds"));
        EditFunds->resize(400, 191);
        EditFunds->setMinimumSize(QSize(400, 191));
        gridLayout = new QGridLayout(EditFunds);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        buttonBox = new QDialogButtonBox(EditFunds);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        QFont font;
        font.setPointSize(12);
        buttonBox->setFont(font);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);

        widEditFunds = new QGridLayout();
        widEditFunds->setObjectName(QStringLiteral("widEditFunds"));
        btnAddToWallet = new QPushButton(EditFunds);
        btnAddToWallet->setObjectName(QStringLiteral("btnAddToWallet"));
        btnAddToWallet->setMinimumSize(QSize(30, 30));
        btnAddToWallet->setMaximumSize(QSize(30, 16777215));
        btnAddToWallet->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/add_black_24dp.svg"), QSize(), QIcon::Normal, QIcon::Off);
        btnAddToWallet->setIcon(icon);
        btnAddToWallet->setIconSize(QSize(24, 24));

        widEditFunds->addWidget(btnAddToWallet, 0, 2, 1, 1);

        lnEditWithdraw = new QLineEdit(EditFunds);
        lnEditWithdraw->setObjectName(QStringLiteral("lnEditWithdraw"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lnEditWithdraw->sizePolicy().hasHeightForWidth());
        lnEditWithdraw->setSizePolicy(sizePolicy);
        lnEditWithdraw->setMinimumSize(QSize(0, 30));
        lnEditWithdraw->setMaximumSize(QSize(100, 16777215));
        lnEditWithdraw->setFont(font);

        widEditFunds->addWidget(lnEditWithdraw, 2, 1, 1, 1);

        btnAddToBank = new QPushButton(EditFunds);
        btnAddToBank->setObjectName(QStringLiteral("btnAddToBank"));
        btnAddToBank->setMinimumSize(QSize(30, 30));
        btnAddToBank->setMaximumSize(QSize(30, 16777215));
        btnAddToBank->setFont(font);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/death_24dp.svg"), QSize(), QIcon::Normal, QIcon::Off);
        btnAddToBank->setIcon(icon1);
        btnAddToBank->setIconSize(QSize(24, 24));

        widEditFunds->addWidget(btnAddToBank, 1, 2, 1, 1);

        lnEditAddToBank = new QLineEdit(EditFunds);
        lnEditAddToBank->setObjectName(QStringLiteral("lnEditAddToBank"));
        sizePolicy.setHeightForWidth(lnEditAddToBank->sizePolicy().hasHeightForWidth());
        lnEditAddToBank->setSizePolicy(sizePolicy);
        lnEditAddToBank->setMinimumSize(QSize(0, 30));
        lnEditAddToBank->setMaximumSize(QSize(100, 16777215));
        lnEditAddToBank->setFont(font);

        widEditFunds->addWidget(lnEditAddToBank, 1, 1, 1, 1);

        btnRecurringPayment = new QPushButton(EditFunds);
        btnRecurringPayment->setObjectName(QStringLiteral("btnRecurringPayment"));
        btnRecurringPayment->setMinimumSize(QSize(30, 30));
        btnRecurringPayment->setMaximumSize(QSize(30, 16777215));
        btnRecurringPayment->setFont(font);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/done_black_24dp.svg"), QSize(), QIcon::Normal, QIcon::Off);
        btnRecurringPayment->setIcon(icon2);
        btnRecurringPayment->setIconSize(QSize(24, 24));

        widEditFunds->addWidget(btnRecurringPayment, 3, 2, 1, 1);

        lnEditRecurringPayment = new QLineEdit(EditFunds);
        lnEditRecurringPayment->setObjectName(QStringLiteral("lnEditRecurringPayment"));
        sizePolicy.setHeightForWidth(lnEditRecurringPayment->sizePolicy().hasHeightForWidth());
        lnEditRecurringPayment->setSizePolicy(sizePolicy);
        lnEditRecurringPayment->setMinimumSize(QSize(0, 30));
        lnEditRecurringPayment->setMaximumSize(QSize(100, 16777215));
        lnEditRecurringPayment->setFont(font);

        widEditFunds->addWidget(lnEditRecurringPayment, 3, 1, 1, 1);

        lblRecurringPayment = new QLabel(EditFunds);
        lblRecurringPayment->setObjectName(QStringLiteral("lblRecurringPayment"));
        lblRecurringPayment->setMinimumSize(QSize(0, 30));
        lblRecurringPayment->setFont(font);

        widEditFunds->addWidget(lblRecurringPayment, 3, 0, 1, 1);

        lblAddToBank = new QLabel(EditFunds);
        lblAddToBank->setObjectName(QStringLiteral("lblAddToBank"));
        lblAddToBank->setMinimumSize(QSize(0, 30));
        lblAddToBank->setFont(font);

        widEditFunds->addWidget(lblAddToBank, 1, 0, 1, 1);

        lblWithdraw = new QLabel(EditFunds);
        lblWithdraw->setObjectName(QStringLiteral("lblWithdraw"));
        lblWithdraw->setMinimumSize(QSize(0, 30));
        lblWithdraw->setFont(font);

        widEditFunds->addWidget(lblWithdraw, 2, 0, 1, 1);

        btnWithdraw = new QPushButton(EditFunds);
        btnWithdraw->setObjectName(QStringLiteral("btnWithdraw"));
        btnWithdraw->setMinimumSize(QSize(30, 30));
        btnWithdraw->setMaximumSize(QSize(30, 16777215));
        btnWithdraw->setFont(font);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/remove_black_24dp.svg"), QSize(), QIcon::Normal, QIcon::Off);
        btnWithdraw->setIcon(icon3);
        btnWithdraw->setIconSize(QSize(24, 24));

        widEditFunds->addWidget(btnWithdraw, 2, 2, 1, 1);

        lnEditAddToWallet = new QLineEdit(EditFunds);
        lnEditAddToWallet->setObjectName(QStringLiteral("lnEditAddToWallet"));
        sizePolicy.setHeightForWidth(lnEditAddToWallet->sizePolicy().hasHeightForWidth());
        lnEditAddToWallet->setSizePolicy(sizePolicy);
        lnEditAddToWallet->setMinimumSize(QSize(0, 30));
        lnEditAddToWallet->setMaximumSize(QSize(100, 16777215));
        lnEditAddToWallet->setFont(font);

        widEditFunds->addWidget(lnEditAddToWallet, 0, 1, 1, 1);

        lblAddToWallet = new QLabel(EditFunds);
        lblAddToWallet->setObjectName(QStringLiteral("lblAddToWallet"));
        lblAddToWallet->setMinimumSize(QSize(0, 30));
        lblAddToWallet->setFont(font);

        widEditFunds->addWidget(lblAddToWallet, 0, 0, 1, 1);


        gridLayout->addLayout(widEditFunds, 0, 0, 1, 1);


        retranslateUi(EditFunds);
        QObject::connect(buttonBox, SIGNAL(accepted()), EditFunds, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), EditFunds, SLOT(reject()));

        QMetaObject::connectSlotsByName(EditFunds);
    } // setupUi

    void retranslateUi(QDialog *EditFunds)
    {
        EditFunds->setWindowTitle(QApplication::translate("EditFunds", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214 \321\201\321\200\320\265\320\264\321\201\321\202\320\262\320\260", nullptr));
        btnAddToWallet->setText(QString());
        btnAddToBank->setText(QString());
        btnRecurringPayment->setText(QString());
        lblRecurringPayment->setText(QApplication::translate("EditFunds", "\320\220\320\262\321\202\320\276\320\274\320\260\321\202\320\270\321\207\320\265\321\201\320\272\320\270\320\271 \320\277\320\265\321\200\320\265\320\262\320\276\320\264 \320\262 \320\272\320\276\320\277\320\270\320\273\320\272\321\203:", nullptr));
        lblAddToBank->setText(QApplication::translate("EditFunds", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\201\321\200\320\265\320\264\321\201\321\202\320\262\320\260 \320\262 \320\272\320\276\320\277\320\270\320\273\320\272\321\203:", nullptr));
        lblWithdraw->setText(QApplication::translate("EditFunds", "\320\230\320\267\321\212\321\217\321\202\321\214 \321\201\321\200\320\265\320\264\321\201\321\202\320\262\320\260 \320\270\320\267 \320\272\320\276\320\277\320\270\320\273\320\272\320\270:", nullptr));
        btnWithdraw->setText(QString());
        lblAddToWallet->setText(QApplication::translate("EditFunds", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\201\321\200\320\265\320\264\321\201\321\202\320\262\320\260 \320\262 \320\272\320\276\321\210\320\265\320\273\321\221\320\272:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditFunds: public Ui_EditFunds {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITFUNDS_H
