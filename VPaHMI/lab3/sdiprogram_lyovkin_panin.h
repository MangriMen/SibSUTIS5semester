#ifndef SDIPROGRAM_LYOVKIN_PANIN_H
#define SDIPROGRAM_LYOVKIN_PANIN_H

#include <QMainWindow>
#include <QMessageBox>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QColorDialog>
#include "docwindow_lyovkin_panin.h"

class SDIProgram_Lyovkin_Panin : public QMainWindow
{
    Q_OBJECT

public:
    explicit SDIProgram_Lyovkin_Panin(QWidget *pwgt = 0): QMainWindow(pwgt)
    {
        QMenu* pmnuFile = new QMenu("&File");
        QAction* pmnuHelp = new QAction("&Help");
        pmnuHelp->setShortcut(QKeySequence("F1"));
        DocWindow_Lyovkin_Panin* pdoc = new DocWindow_Lyovkin_Panin;

        pmnuFile->addAction("&Open...",
                    pdoc,
                    SLOT(slotLoad()),
                    QKeySequence("CTRL+O"));
        pmnuFile->addAction("&Save",
                    pdoc,
                    SLOT(slotSaveAs()),
                    QKeySequence("CTRL+S"));
        pmnuFile->addAction("&Color",
                    pdoc,
                    SLOT(slotChangeColor()),
                    QKeySequence("ALT+C"));

        menuBar()->addMenu(pmnuFile);
        menuBar()->addAction(pmnuHelp);

        setCentralWidget(pdoc);

        connect(
                pdoc,
                SIGNAL(changeWindowTitle(const QString&)),
                SLOT(slotChangeWindowTitle(const QString&))
                );

        connect(
                pmnuHelp,
                SIGNAL(triggered()),
                SLOT(slotAbout())
                );

        statusBar()->showMessage("Ready", 2000);

        resize(640, 480);
    }

public slots:
    void slotAbout()
    {
        QMessageBox::about(this, "Application", "ИП-912 Лёвкин Игорь и Панин Никита");
    }

    void slotChangeWindowTitle(const QString& str)
    {
        setWindowTitle(str);
    }
};

#endif // SDIPROGRAM_LYOVKIN_PANIN_H
