/********************************************************************************
** Form generated from reading UI file 'error.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ERROR_H
#define UI_ERROR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_error
{
public:
    QGridLayout *gridLayout;
    QDialogButtonBox *buttonBox;
    QLabel *lblErrorText;

    void setupUi(QDialog *error)
    {
        if (error->objectName().isEmpty())
            error->setObjectName(QStringLiteral("error"));
        error->resize(320, 144);
        error->setMinimumSize(QSize(320, 144));
        error->setMaximumSize(QSize(320, 144));
        gridLayout = new QGridLayout(error);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        buttonBox = new QDialogButtonBox(error);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(12);
        buttonBox->setFont(font);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);

        lblErrorText = new QLabel(error);
        lblErrorText->setObjectName(QStringLiteral("lblErrorText"));
        lblErrorText->setFont(font);

        gridLayout->addWidget(lblErrorText, 0, 0, 1, 1);


        retranslateUi(error);
        QObject::connect(buttonBox, SIGNAL(accepted()), error, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), error, SLOT(reject()));

        QMetaObject::connectSlotsByName(error);
    } // setupUi

    void retranslateUi(QDialog *error)
    {
        error->setWindowTitle(QApplication::translate("error", "\320\236\321\210\320\270\320\261\320\272\320\260", nullptr));
        lblErrorText->setText(QApplication::translate("error", "\320\227\320\264\320\265\321\201\321\214 \320\261\321\203\320\264\320\265\321\202 \320\277\321\200\320\265\320\264\321\201\321\202\320\260\320\262\320\273\320\265\320\275 \321\202\320\265\320\272\321\201\321\202 \320\276\321\210\320\270\320\261\320\272\320\270.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class error: public Ui_error {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ERROR_H
