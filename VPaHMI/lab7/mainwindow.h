#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QGraphicsProxyWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnTestPost_clicked();

private:
    QMap<QString, QGraphicsProxyWidget*> elements;
    Ui::MainWindow *ui;
    void resizeEvent(QResizeEvent *);
};

#endif // MAINWINDOW_H
