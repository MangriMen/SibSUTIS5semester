#include "docwindow_lyovkin_panin.h"
#include <QFileDialog>
#include <QTextStream>
#include <QColorDialog>
#include <QDebug>

DocWindow_Lyovkin_Panin::DocWindow_Lyovkin_Panin(QWidget* pwgt): QTextEdit(pwgt)
{

}

void DocWindow_Lyovkin_Panin::slotLoad()
{
    QString str = QFileDialog::getOpenFileName();
    if (str.isEmpty()) {
        return;
    }

    QColor oldColor = textColor();
    qDebug() << oldColor.name();
    setTextColor(QColor(Qt::black));

    QFile file(str);
    if (file.open(QIODevice::ReadOnly)) {

        QTextStream stream(&file);
        setPlainText(stream.readAll());
        file.close();


        m_strFileName = str;
        emit changeWindowTitle(m_strFileName);
    }

    setTextColor(oldColor);
    qDebug() << textColor().name();
}

void DocWindow_Lyovkin_Panin::slotSaveAs()
{
    QString str = QFileDialog::getSaveFileName(0, m_strFileName);
    if (!str.isEmpty()) {
        m_strFileName = str;
        slotSave();
    }
}

void DocWindow_Lyovkin_Panin::slotSave()
{
    if (m_strFileName.isEmpty()) {
        slotSaveAs();
        return;
    }

    QFile file(m_strFileName);

    if (file.open(QIODevice::WriteOnly)){
        QTextStream(&file)<<toPlainText();
        file.close();
        emit changeWindowTitle(m_strFileName);
    }
}

void DocWindow_Lyovkin_Panin::slotChangeColor() {
    QColor newColor = QColorDialog::getColor();
    setTextColor(newColor);
}
