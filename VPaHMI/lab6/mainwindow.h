#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "lyovkin_panin.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Lyovkin_Panin *myForm;
signals:
    void sendData(QString str);
private slots:
    void generateAndSendData();
    void loadPhoto();
};

#endif // MAINWINDOW_H
