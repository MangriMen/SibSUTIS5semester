#include "sdiprogram_lyovkin_panin.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTime>
#include <unistd.h>
#include <QFontMetrics>

void loadModules(QSplashScreen* psplash){
    QTime time;
    time.start();

    QRect fmRect = qApp->fontMetrics().boundingRect("Loading modules: 100%");
    psplash->setPixmap(psplash->pixmap().scaledToWidth(fmRect.width()+20));

    for (int i=0; i < 100; ) {
        if (time.elapsed() > 40) {
            time.start();
            ++i;
        }
        psplash->showMessage("Loading modules: "
                             + QString::number(i) + "%",
                             Qt::AlignCenter,
                             Qt::black
                             );
        qApp->processEvents();
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen splash(QPixmap(":/s.png").scaledToWidth(256));
    splash.show();
    SDIProgram_Lyovkin_Panin w;
    loadModules(&splash);
    splash.finish(&w);
    w.show();

    return a.exec();
}
