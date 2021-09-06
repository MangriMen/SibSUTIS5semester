#ifndef DOCWINDOW_LYOVKIN_PANIN_H
#define DOCWINDOW_LYOVKIN_PANIN_H
#include <QTextEdit>


class DocWindow_Lyovkin_Panin: public QTextEdit
{
    Q_OBJECT
private:
    QString m_strFileName;

public:
    DocWindow_Lyovkin_Panin(QWidget* pwgt = 0);
signals:
    void changeWindowTitle(const QString&);

public slots:
    void slotLoad();
    void slotSave();
    void slotSaveAs();
    void slotChangeColor();
};

#endif // DOCWINDOW_LYOVKIN_PANIN_H
