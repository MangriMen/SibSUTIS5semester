/********************************************************************************
** Form generated from reading UI file 'goals.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GOALS_H
#define UI_GOALS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_Goals
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QGridLayout *widMainGrid;
    QLabel *lblAddEditImage;
    QGridLayout *widCurrentGoalData;
    QLabel *lblGoalPriceDivider;
    QLabel *lblCurrentGoalPrice;
    QLabel *lblCurrentGoalMoneySpent;
    QSpacerItem *horizontalSpacer_2;
    QLabel *lblBankBalanceText;
    QLabel *lblCurrentGoalNameText;
    QSpacerItem *horizontalSpacer_3;
    QLabel *lblBankBalance;
    QLabel *lblCurrentGoalText;
    QGridLayout *widFundManagement;
    QLineEdit *lnEditTransfer;
    QLabel *lblWithdrawText;
    QLineEdit *lnEditWithdraw;
    QLabel *lblTransferText;
    QPushButton *btnTransferAccept;
    QPushButton *btnWithdrawAccept;
    QSpacerItem *horizontalSpacer;
    QLabel *lblAddEditText;
    QGridLayout *widAddEdit;
    QComboBox *cmbAddIncomesexpences;
    QPushButton *btnDeleteGoal;
    QLineEdit *lnEditAddEdit;
    QPushButton *btnMakeCurrent;
    QPushButton *btnDiscardGoal;
    QFrame *line;
    QLabel *lblCurrentGoalImage;
    QFrame *line_2;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Goals)
    {
        if (Goals->objectName().isEmpty())
            Goals->setObjectName(QStringLiteral("Goals"));
        Goals->resize(502, 341);
        Goals->setMinimumSize(QSize(502, 341));
        Goals->setMaximumSize(QSize(502, 341));
        gridLayout = new QGridLayout(Goals);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(9, 5, 9, -1);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widMainGrid = new QGridLayout();
        widMainGrid->setObjectName(QStringLiteral("widMainGrid"));
        lblAddEditImage = new QLabel(Goals);
        lblAddEditImage->setObjectName(QStringLiteral("lblAddEditImage"));
        lblAddEditImage->setMaximumSize(QSize(100, 100));
        QFont font;
        font.setPointSize(12);
        lblAddEditImage->setFont(font);
        lblAddEditImage->setFrameShape(QFrame::Box);
        lblAddEditImage->setFrameShadow(QFrame::Raised);
        lblAddEditImage->setPixmap(QPixmap(QString::fromUtf8(":/images/image_black_24dp.svg")));
        lblAddEditImage->setScaledContents(false);
        lblAddEditImage->setAlignment(Qt::AlignCenter);

        widMainGrid->addWidget(lblAddEditImage, 5, 1, 2, 1);

        widCurrentGoalData = new QGridLayout();
        widCurrentGoalData->setObjectName(QStringLiteral("widCurrentGoalData"));
        widCurrentGoalData->setContentsMargins(-1, 0, -1, -1);
        lblGoalPriceDivider = new QLabel(Goals);
        lblGoalPriceDivider->setObjectName(QStringLiteral("lblGoalPriceDivider"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lblGoalPriceDivider->sizePolicy().hasHeightForWidth());
        lblGoalPriceDivider->setSizePolicy(sizePolicy);
        lblGoalPriceDivider->setFont(font);

        widCurrentGoalData->addWidget(lblGoalPriceDivider, 0, 3, 1, 1);

        lblCurrentGoalPrice = new QLabel(Goals);
        lblCurrentGoalPrice->setObjectName(QStringLiteral("lblCurrentGoalPrice"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lblCurrentGoalPrice->sizePolicy().hasHeightForWidth());
        lblCurrentGoalPrice->setSizePolicy(sizePolicy1);
        lblCurrentGoalPrice->setFont(font);
        lblCurrentGoalPrice->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        widCurrentGoalData->addWidget(lblCurrentGoalPrice, 0, 4, 1, 1);

        lblCurrentGoalMoneySpent = new QLabel(Goals);
        lblCurrentGoalMoneySpent->setObjectName(QStringLiteral("lblCurrentGoalMoneySpent"));
        sizePolicy1.setHeightForWidth(lblCurrentGoalMoneySpent->sizePolicy().hasHeightForWidth());
        lblCurrentGoalMoneySpent->setSizePolicy(sizePolicy1);
        lblCurrentGoalMoneySpent->setFont(font);

        widCurrentGoalData->addWidget(lblCurrentGoalMoneySpent, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        widCurrentGoalData->addItem(horizontalSpacer_2, 0, 5, 1, 1);

        lblBankBalanceText = new QLabel(Goals);
        lblBankBalanceText->setObjectName(QStringLiteral("lblBankBalanceText"));
        sizePolicy1.setHeightForWidth(lblBankBalanceText->sizePolicy().hasHeightForWidth());
        lblBankBalanceText->setSizePolicy(sizePolicy1);
        lblBankBalanceText->setFont(font);

        widCurrentGoalData->addWidget(lblBankBalanceText, 1, 0, 1, 1);

        lblCurrentGoalNameText = new QLabel(Goals);
        lblCurrentGoalNameText->setObjectName(QStringLiteral("lblCurrentGoalNameText"));
        sizePolicy1.setHeightForWidth(lblCurrentGoalNameText->sizePolicy().hasHeightForWidth());
        lblCurrentGoalNameText->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        lblCurrentGoalNameText->setFont(font1);

        widCurrentGoalData->addWidget(lblCurrentGoalNameText, 0, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        widCurrentGoalData->addItem(horizontalSpacer_3, 0, 6, 1, 1);

        lblBankBalance = new QLabel(Goals);
        lblBankBalance->setObjectName(QStringLiteral("lblBankBalance"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lblBankBalance->sizePolicy().hasHeightForWidth());
        lblBankBalance->setSizePolicy(sizePolicy2);
        lblBankBalance->setFont(font);

        widCurrentGoalData->addWidget(lblBankBalance, 1, 2, 1, 4);


        widMainGrid->addLayout(widCurrentGoalData, 2, 0, 1, 1);

        lblCurrentGoalText = new QLabel(Goals);
        lblCurrentGoalText->setObjectName(QStringLiteral("lblCurrentGoalText"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lblCurrentGoalText->sizePolicy().hasHeightForWidth());
        lblCurrentGoalText->setSizePolicy(sizePolicy3);
        QFont font2;
        font2.setPointSize(16);
        lblCurrentGoalText->setFont(font2);

        widMainGrid->addWidget(lblCurrentGoalText, 0, 0, 1, 1);

        widFundManagement = new QGridLayout();
        widFundManagement->setObjectName(QStringLiteral("widFundManagement"));
        widFundManagement->setContentsMargins(-1, 0, -1, -1);
        lnEditTransfer = new QLineEdit(Goals);
        lnEditTransfer->setObjectName(QStringLiteral("lnEditTransfer"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(lnEditTransfer->sizePolicy().hasHeightForWidth());
        lnEditTransfer->setSizePolicy(sizePolicy4);
        lnEditTransfer->setMinimumSize(QSize(0, 30));
        lnEditTransfer->setMaximumSize(QSize(80, 16777215));
        lnEditTransfer->setFont(font);

        widFundManagement->addWidget(lnEditTransfer, 0, 1, 1, 1);

        lblWithdrawText = new QLabel(Goals);
        lblWithdrawText->setObjectName(QStringLiteral("lblWithdrawText"));
        sizePolicy1.setHeightForWidth(lblWithdrawText->sizePolicy().hasHeightForWidth());
        lblWithdrawText->setSizePolicy(sizePolicy1);
        lblWithdrawText->setMinimumSize(QSize(0, 30));
        lblWithdrawText->setFont(font);

        widFundManagement->addWidget(lblWithdrawText, 2, 0, 1, 1);

        lnEditWithdraw = new QLineEdit(Goals);
        lnEditWithdraw->setObjectName(QStringLiteral("lnEditWithdraw"));
        sizePolicy3.setHeightForWidth(lnEditWithdraw->sizePolicy().hasHeightForWidth());
        lnEditWithdraw->setSizePolicy(sizePolicy3);
        lnEditWithdraw->setMinimumSize(QSize(0, 30));
        lnEditWithdraw->setMaximumSize(QSize(80, 16777215));
        lnEditWithdraw->setFont(font);

        widFundManagement->addWidget(lnEditWithdraw, 2, 1, 1, 1);

        lblTransferText = new QLabel(Goals);
        lblTransferText->setObjectName(QStringLiteral("lblTransferText"));
        sizePolicy1.setHeightForWidth(lblTransferText->sizePolicy().hasHeightForWidth());
        lblTransferText->setSizePolicy(sizePolicy1);
        lblTransferText->setMinimumSize(QSize(0, 30));
        lblTransferText->setFont(font);

        widFundManagement->addWidget(lblTransferText, 0, 0, 1, 1);

        btnTransferAccept = new QPushButton(Goals);
        btnTransferAccept->setObjectName(QStringLiteral("btnTransferAccept"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(btnTransferAccept->sizePolicy().hasHeightForWidth());
        btnTransferAccept->setSizePolicy(sizePolicy5);
        btnTransferAccept->setMinimumSize(QSize(0, 30));
        btnTransferAccept->setMaximumSize(QSize(30, 30));
        btnTransferAccept->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/add_black_24dp.svg"), QSize(), QIcon::Normal, QIcon::Off);
        btnTransferAccept->setIcon(icon);
        btnTransferAccept->setIconSize(QSize(24, 24));

        widFundManagement->addWidget(btnTransferAccept, 0, 2, 1, 1);

        btnWithdrawAccept = new QPushButton(Goals);
        btnWithdrawAccept->setObjectName(QStringLiteral("btnWithdrawAccept"));
        sizePolicy5.setHeightForWidth(btnWithdrawAccept->sizePolicy().hasHeightForWidth());
        btnWithdrawAccept->setSizePolicy(sizePolicy5);
        btnWithdrawAccept->setMinimumSize(QSize(0, 30));
        btnWithdrawAccept->setMaximumSize(QSize(30, 30));
        btnWithdrawAccept->setFont(font);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/remove_black_24dp.svg"), QSize(), QIcon::Normal, QIcon::Off);
        btnWithdrawAccept->setIcon(icon1);
        btnWithdrawAccept->setIconSize(QSize(24, 24));

        widFundManagement->addWidget(btnWithdrawAccept, 2, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        widFundManagement->addItem(horizontalSpacer, 0, 3, 1, 1);


        widMainGrid->addLayout(widFundManagement, 3, 0, 1, 1);

        lblAddEditText = new QLabel(Goals);
        lblAddEditText->setObjectName(QStringLiteral("lblAddEditText"));
        lblAddEditText->setFont(font);

        widMainGrid->addWidget(lblAddEditText, 5, 0, 1, 1);

        widAddEdit = new QGridLayout();
        widAddEdit->setObjectName(QStringLiteral("widAddEdit"));
        cmbAddIncomesexpences = new QComboBox(Goals);
        cmbAddIncomesexpences->setObjectName(QStringLiteral("cmbAddIncomesexpences"));
        cmbAddIncomesexpences->setMinimumSize(QSize(0, 30));
        cmbAddIncomesexpences->setFont(font);

        widAddEdit->addWidget(cmbAddIncomesexpences, 0, 0, 1, 3);

        btnDeleteGoal = new QPushButton(Goals);
        btnDeleteGoal->setObjectName(QStringLiteral("btnDeleteGoal"));
        btnDeleteGoal->setMinimumSize(QSize(0, 30));
        btnDeleteGoal->setMaximumSize(QSize(30, 30));
        btnDeleteGoal->setFont(font);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/delete_black_24dp.svg"), QSize(), QIcon::Normal, QIcon::Off);
        btnDeleteGoal->setIcon(icon2);
        btnDeleteGoal->setIconSize(QSize(24, 24));

        widAddEdit->addWidget(btnDeleteGoal, 0, 3, 1, 1);

        lnEditAddEdit = new QLineEdit(Goals);
        lnEditAddEdit->setObjectName(QStringLiteral("lnEditAddEdit"));
        sizePolicy4.setHeightForWidth(lnEditAddEdit->sizePolicy().hasHeightForWidth());
        lnEditAddEdit->setSizePolicy(sizePolicy4);
        lnEditAddEdit->setMinimumSize(QSize(0, 30));
        lnEditAddEdit->setMaximumSize(QSize(80, 30));
        lnEditAddEdit->setFont(font);

        widAddEdit->addWidget(lnEditAddEdit, 2, 0, 1, 1);

        btnMakeCurrent = new QPushButton(Goals);
        btnMakeCurrent->setObjectName(QStringLiteral("btnMakeCurrent"));
        btnMakeCurrent->setMinimumSize(QSize(0, 30));
        btnMakeCurrent->setMaximumSize(QSize(16777215, 30));
        btnMakeCurrent->setFont(font);

        widAddEdit->addWidget(btnMakeCurrent, 2, 1, 1, 1);

        btnDiscardGoal = new QPushButton(Goals);
        btnDiscardGoal->setObjectName(QStringLiteral("btnDiscardGoal"));
        btnDiscardGoal->setMaximumSize(QSize(16777215, 30));
        btnDiscardGoal->setFont(font);
        btnDiscardGoal->setIconSize(QSize(24, 24));

        widAddEdit->addWidget(btnDiscardGoal, 2, 2, 1, 2);


        widMainGrid->addLayout(widAddEdit, 6, 0, 1, 1);

        line = new QFrame(Goals);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShadow(QFrame::Raised);
        line->setFrameShape(QFrame::HLine);

        widMainGrid->addWidget(line, 4, 0, 1, 2);

        lblCurrentGoalImage = new QLabel(Goals);
        lblCurrentGoalImage->setObjectName(QStringLiteral("lblCurrentGoalImage"));
        lblCurrentGoalImage->setMaximumSize(QSize(100, 100));
        lblCurrentGoalImage->setFont(font);
        lblCurrentGoalImage->setFrameShape(QFrame::Box);
        lblCurrentGoalImage->setFrameShadow(QFrame::Raised);
        lblCurrentGoalImage->setPixmap(QPixmap(QString::fromUtf8(":/images/image_black_24dp.svg")));
        lblCurrentGoalImage->setScaledContents(false);
        lblCurrentGoalImage->setAlignment(Qt::AlignCenter);

        widMainGrid->addWidget(lblCurrentGoalImage, 2, 1, 2, 1);

        line_2 = new QFrame(Goals);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShadow(QFrame::Raised);
        line_2->setFrameShape(QFrame::HLine);

        widMainGrid->addWidget(line_2, 1, 0, 1, 2);


        horizontalLayout->addLayout(widMainGrid);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(10, 8, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(Goals);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setFont(font);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 1);


        retranslateUi(Goals);
        QObject::connect(buttonBox, SIGNAL(accepted()), Goals, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Goals, SLOT(reject()));

        QMetaObject::connectSlotsByName(Goals);
    } // setupUi

    void retranslateUi(QDialog *Goals)
    {
        Goals->setWindowTitle(QApplication::translate("Goals", "\320\234\320\265\320\275\321\216 \321\206\320\265\320\273\320\265\320\271", nullptr));
        lblAddEditImage->setText(QString());
        lblGoalPriceDivider->setText(QApplication::translate("Goals", "/", nullptr));
        lblCurrentGoalPrice->setText(QApplication::translate("Goals", "0\321\200", nullptr));
        lblCurrentGoalMoneySpent->setText(QApplication::translate("Goals", "0\321\200", nullptr));
        lblBankBalanceText->setText(QApplication::translate("Goals", "\320\221\320\260\320\273\320\260\320\275\321\201 \320\272\320\276\320\277\320\270\320\273\320\272\320\270:", nullptr));
        lblCurrentGoalNameText->setText(QApplication::translate("Goals", "\320\237\320\276\320\272\321\203\320\277\320\272\320\260 \320\261\320\260\321\201 \320\263\320\270\321\202\320\260\321\200\321\213", nullptr));
        lblBankBalance->setText(QApplication::translate("Goals", "0\321\200", nullptr));
        lblCurrentGoalText->setText(QApplication::translate("Goals", "\320\242\320\265\320\272\321\203\321\211\320\260\321\217 \321\206\320\265\320\273\321\214:", nullptr));
        lblWithdrawText->setText(QApplication::translate("Goals", "\320\241\320\275\321\217\321\202\321\214 \321\201\320\276 \321\201\321\207\321\221\321\202\320\260 \321\206\320\265\320\273\320\270:", nullptr));
        lblTransferText->setText(QApplication::translate("Goals", "\320\237\320\265\321\200\320\265\320\262\320\265\321\201\321\202\320\270 \320\275\320\260 \321\201\321\207\321\221\321\202 \321\206\320\265\320\273\320\270:", nullptr));
        btnTransferAccept->setText(QString());
        btnWithdrawAccept->setText(QString());
        lblAddEditText->setText(QApplication::translate("Goals", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 / \320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        btnDeleteGoal->setText(QString());
        btnMakeCurrent->setText(QApplication::translate("Goals", "\320\241\320\264\320\265\320\273\320\260\321\202\321\214 \321\202\320\265\320\272\321\203\321\211\320\265\320\271", nullptr));
        btnDiscardGoal->setText(QApplication::translate("Goals", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214 \321\206\320\265\320\273\321\214", nullptr));
        lblCurrentGoalImage->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Goals: public Ui_Goals {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GOALS_H
