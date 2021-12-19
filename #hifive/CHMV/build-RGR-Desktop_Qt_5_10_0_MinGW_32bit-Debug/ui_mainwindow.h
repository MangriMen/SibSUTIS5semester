/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <widgetbutton.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QWidget *widAccountData;
    QGridLayout *gridLayout_3;
    QLabel *lblAccountText;
    QLabel *lblAccountName;
    QPushButton *btnAccountDelete;
    WidgetButton *widFunds;
    QGridLayout *gridLayout_2;
    QLabel *lblBankText;
    QLabel *lblWalletText;
    QLabel *lblWalletBalance;
    QLabel *lblBankBalance;
    WidgetButton *widGoals;
    QHBoxLayout *horizontalLayout;
    QLabel *lblCurrentGoal;
    QLabel *lblCurrentGoalText;
    QLabel *lblCurrentGoalMoneySpent;
    QLabel *lblGoalPriceDivider;
    QLabel *lblCurrentGoalPrice;
    QLabel *lblCurrentGoalImg;
    WidgetButton *grBoxIncomes;
    QVBoxLayout *verticalLayout_2;
    QTableView *listWidIncomes;
    QLabel *lblIncomesTotal;
    WidgetButton *grBoxExpenses;
    QVBoxLayout *verticalLayout_3;
    QTableView *listWidExpenses;
    QLabel *lblExpensesTotal;
    QMenuBar *menuBar;
    QMenu *menuBtnUser;
    QMenu *menuBtnInfo;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(656, 357);
        MainWindow->setMinimumSize(QSize(656, 357));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 1, 1, 1);

        widAccountData = new QWidget(centralWidget);
        widAccountData->setObjectName(QStringLiteral("widAccountData"));
        QFont font;
        font.setPointSize(12);
        widAccountData->setFont(font);
        gridLayout_3 = new QGridLayout(widAccountData);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        lblAccountText = new QLabel(widAccountData);
        lblAccountText->setObjectName(QStringLiteral("lblAccountText"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lblAccountText->sizePolicy().hasHeightForWidth());
        lblAccountText->setSizePolicy(sizePolicy);
        lblAccountText->setFont(font);

        gridLayout_3->addWidget(lblAccountText, 0, 0, 1, 1);

        lblAccountName = new QLabel(widAccountData);
        lblAccountName->setObjectName(QStringLiteral("lblAccountName"));
        lblAccountName->setFont(font);

        gridLayout_3->addWidget(lblAccountName, 0, 1, 1, 1);

        btnAccountDelete = new QPushButton(widAccountData);
        btnAccountDelete->setObjectName(QStringLiteral("btnAccountDelete"));
        btnAccountDelete->setMaximumSize(QSize(30, 30));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/delete_black_24dp.svg"), QSize(), QIcon::Normal, QIcon::Off);
        btnAccountDelete->setIcon(icon);
        btnAccountDelete->setIconSize(QSize(24, 24));

        gridLayout_3->addWidget(btnAccountDelete, 0, 2, 1, 1);

        widFunds = new WidgetButton(widAccountData);
        widFunds->setObjectName(QStringLiteral("widFunds"));
        widFunds->setFont(font);
        gridLayout_2 = new QGridLayout(widFunds);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        lblBankText = new QLabel(widFunds);
        lblBankText->setObjectName(QStringLiteral("lblBankText"));
        lblBankText->setFont(font);

        gridLayout_2->addWidget(lblBankText, 1, 0, 1, 1);

        lblWalletText = new QLabel(widFunds);
        lblWalletText->setObjectName(QStringLiteral("lblWalletText"));
        lblWalletText->setFont(font);

        gridLayout_2->addWidget(lblWalletText, 3, 0, 1, 1);

        lblWalletBalance = new QLabel(widFunds);
        lblWalletBalance->setObjectName(QStringLiteral("lblWalletBalance"));
        lblWalletBalance->setFont(font);

        gridLayout_2->addWidget(lblWalletBalance, 3, 1, 1, 1);

        lblBankBalance = new QLabel(widFunds);
        lblBankBalance->setObjectName(QStringLiteral("lblBankBalance"));
        lblBankBalance->setFont(font);

        gridLayout_2->addWidget(lblBankBalance, 1, 1, 1, 1);


        gridLayout_3->addWidget(widFunds, 1, 0, 1, 3);


        gridLayout->addWidget(widAccountData, 0, 1, 1, 1);

        widGoals = new WidgetButton(centralWidget);
        widGoals->setObjectName(QStringLiteral("widGoals"));
        sizePolicy.setHeightForWidth(widGoals->sizePolicy().hasHeightForWidth());
        widGoals->setSizePolicy(sizePolicy);
        widGoals->setFont(font);
        horizontalLayout = new QHBoxLayout(widGoals);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lblCurrentGoal = new QLabel(widGoals);
        lblCurrentGoal->setObjectName(QStringLiteral("lblCurrentGoal"));
        lblCurrentGoal->setFont(font);

        horizontalLayout->addWidget(lblCurrentGoal);

        lblCurrentGoalText = new QLabel(widGoals);
        lblCurrentGoalText->setObjectName(QStringLiteral("lblCurrentGoalText"));
        lblCurrentGoalText->setFont(font);
        lblCurrentGoalText->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(lblCurrentGoalText);

        lblCurrentGoalMoneySpent = new QLabel(widGoals);
        lblCurrentGoalMoneySpent->setObjectName(QStringLiteral("lblCurrentGoalMoneySpent"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lblCurrentGoalMoneySpent->sizePolicy().hasHeightForWidth());
        lblCurrentGoalMoneySpent->setSizePolicy(sizePolicy1);
        lblCurrentGoalMoneySpent->setFont(font);

        horizontalLayout->addWidget(lblCurrentGoalMoneySpent);

        lblGoalPriceDivider = new QLabel(widGoals);
        lblGoalPriceDivider->setObjectName(QStringLiteral("lblGoalPriceDivider"));
        sizePolicy1.setHeightForWidth(lblGoalPriceDivider->sizePolicy().hasHeightForWidth());
        lblGoalPriceDivider->setSizePolicy(sizePolicy1);
        lblGoalPriceDivider->setFont(font);

        horizontalLayout->addWidget(lblGoalPriceDivider);

        lblCurrentGoalPrice = new QLabel(widGoals);
        lblCurrentGoalPrice->setObjectName(QStringLiteral("lblCurrentGoalPrice"));
        sizePolicy1.setHeightForWidth(lblCurrentGoalPrice->sizePolicy().hasHeightForWidth());
        lblCurrentGoalPrice->setSizePolicy(sizePolicy1);
        lblCurrentGoalPrice->setFont(font);

        horizontalLayout->addWidget(lblCurrentGoalPrice);

        lblCurrentGoalImg = new QLabel(widGoals);
        lblCurrentGoalImg->setObjectName(QStringLiteral("lblCurrentGoalImg"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lblCurrentGoalImg->sizePolicy().hasHeightForWidth());
        lblCurrentGoalImg->setSizePolicy(sizePolicy2);
        lblCurrentGoalImg->setMinimumSize(QSize(50, 50));
        lblCurrentGoalImg->setMaximumSize(QSize(50, 50));
        lblCurrentGoalImg->setFont(font);
        lblCurrentGoalImg->setPixmap(QPixmap(QString::fromUtf8(":/images/image_black_24dp.svg")));
        lblCurrentGoalImg->setScaledContents(true);

        horizontalLayout->addWidget(lblCurrentGoalImg);


        gridLayout->addWidget(widGoals, 2, 1, 1, 3);

        grBoxIncomes = new WidgetButton(centralWidget);
        grBoxIncomes->setObjectName(QStringLiteral("grBoxIncomes"));
        grBoxIncomes->setFont(font);
        verticalLayout_2 = new QVBoxLayout(grBoxIncomes);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        listWidIncomes = new QTableView(grBoxIncomes);
        listWidIncomes->setObjectName(QStringLiteral("listWidIncomes"));
        listWidIncomes->setFont(font);
        listWidIncomes->setSelectionMode(QAbstractItemView::NoSelection);
        listWidIncomes->setTextElideMode(Qt::ElideRight);
        listWidIncomes->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        listWidIncomes->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        listWidIncomes->horizontalHeader()->setCascadingSectionResizes(true);
        listWidIncomes->horizontalHeader()->setDefaultSectionSize(80);
        listWidIncomes->horizontalHeader()->setMinimumSectionSize(80);
        listWidIncomes->horizontalHeader()->setStretchLastSection(false);

        verticalLayout_2->addWidget(listWidIncomes);

        lblIncomesTotal = new QLabel(grBoxIncomes);
        lblIncomesTotal->setObjectName(QStringLiteral("lblIncomesTotal"));
        sizePolicy.setHeightForWidth(lblIncomesTotal->sizePolicy().hasHeightForWidth());
        lblIncomesTotal->setSizePolicy(sizePolicy);
        lblIncomesTotal->setFont(font);
        lblIncomesTotal->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(lblIncomesTotal);


        gridLayout->addWidget(grBoxIncomes, 0, 2, 2, 1);

        grBoxExpenses = new WidgetButton(centralWidget);
        grBoxExpenses->setObjectName(QStringLiteral("grBoxExpenses"));
        grBoxExpenses->setFont(font);
        grBoxExpenses->setCursor(QCursor(Qt::PointingHandCursor));
        verticalLayout_3 = new QVBoxLayout(grBoxExpenses);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        listWidExpenses = new QTableView(grBoxExpenses);
        listWidExpenses->setObjectName(QStringLiteral("listWidExpenses"));
        listWidExpenses->setFont(font);
        listWidExpenses->setSelectionMode(QAbstractItemView::NoSelection);
        listWidExpenses->setTextElideMode(Qt::ElideRight);
        listWidExpenses->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        listWidExpenses->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        listWidExpenses->horizontalHeader()->setCascadingSectionResizes(true);
        listWidExpenses->horizontalHeader()->setDefaultSectionSize(80);
        listWidExpenses->horizontalHeader()->setMinimumSectionSize(80);
        listWidExpenses->horizontalHeader()->setStretchLastSection(false);

        verticalLayout_3->addWidget(listWidExpenses);

        lblExpensesTotal = new QLabel(grBoxExpenses);
        lblExpensesTotal->setObjectName(QStringLiteral("lblExpensesTotal"));
        sizePolicy.setHeightForWidth(lblExpensesTotal->sizePolicy().hasHeightForWidth());
        lblExpensesTotal->setSizePolicy(sizePolicy);
        lblExpensesTotal->setFont(font);
        lblExpensesTotal->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(lblExpensesTotal);


        gridLayout->addWidget(grBoxExpenses, 0, 3, 2, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 656, 21));
        menuBtnUser = new QMenu(menuBar);
        menuBtnUser->setObjectName(QStringLiteral("menuBtnUser"));
        menuBtnInfo = new QMenu(menuBar);
        menuBtnInfo->setObjectName(QStringLiteral("menuBtnInfo"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuBtnUser->menuAction());
        menuBar->addAction(menuBtnInfo->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        lblAccountText->setText(QApplication::translate("MainWindow", "\320\220\320\272\320\272\320\260\321\203\320\275\321\202:", nullptr));
        lblAccountName->setText(QApplication::translate("MainWindow", "\320\235\320\265\320\270\320\267\320\262\320\265\321\201\321\202\320\275\320\276", nullptr));
        btnAccountDelete->setText(QString());
        lblBankText->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\277\320\270\320\273\320\272\320\260:", nullptr));
        lblWalletText->setText(QApplication::translate("MainWindow", "\320\232\320\276\321\210\320\265\320\273\321\221\320\272:", nullptr));
        lblWalletBalance->setText(QApplication::translate("MainWindow", "0\321\200", nullptr));
        lblBankBalance->setText(QApplication::translate("MainWindow", "0\321\200", nullptr));
        lblCurrentGoal->setText(QApplication::translate("MainWindow", "\320\242\320\265\320\272\321\203\321\211\320\260\321\217 \321\206\320\265\320\273\321\214:", nullptr));
        lblCurrentGoalText->setText(QApplication::translate("MainWindow", "\320\235\320\265\321\202 \321\206\320\265\320\273\320\270", nullptr));
        lblCurrentGoalMoneySpent->setText(QApplication::translate("MainWindow", "0\321\200", nullptr));
        lblGoalPriceDivider->setText(QApplication::translate("MainWindow", "/", nullptr));
        lblCurrentGoalPrice->setText(QApplication::translate("MainWindow", "0\321\200", nullptr));
        lblCurrentGoalImg->setText(QString());
        lblIncomesTotal->setText(QApplication::translate("MainWindow", "+0\321\200", nullptr));
        lblExpensesTotal->setText(QApplication::translate("MainWindow", "-0\321\200", nullptr));
        menuBtnUser->setTitle(QApplication::translate("MainWindow", "\320\237\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\214", nullptr));
        menuBtnInfo->setTitle(QApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
