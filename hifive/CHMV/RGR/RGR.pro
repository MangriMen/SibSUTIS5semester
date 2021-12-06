#-------------------------------------------------
#
# Project created by QtCreator 2021-11-21T18:46:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RGR
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    editfunds.cpp \
    goals.cpp \
    incomesexpenses.cpp \
    accountcreation.cpp \
    error.cpp

HEADERS += \
        mainwindow.h \
    editfunds.h \
    goals.h \
    incomesexpenses.h \
    accountcreation.h \
    error.h

FORMS += \
        mainwindow.ui \
    editfunds.ui \
    goals.ui \
    incomesexpenses.ui \
    accountcreation.ui \
    error.ui

RESOURCES += \
    resources.qrc
