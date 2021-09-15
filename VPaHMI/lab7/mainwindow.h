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
    QGraphicsPixmapItem* tree;
    QGraphicsItemGroup* bird;
    QList<QGraphicsRectItem*>* borders;
    QPoint* dXY;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void moveAndCheck();
    void resizeTrigger();

private:
    QMap<QString, QGraphicsProxyWidget*> elements;
    Ui::MainWindow *ui;
    void resizeEvent(QResizeEvent *);
};

#endif // MAINWINDOW_H
