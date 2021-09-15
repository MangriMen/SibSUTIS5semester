#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QGraphicsProxyWidget>
#include <QDialog>
#include <QSpinBox>
#include <QDebug>
#include <QColor>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene* scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0, 0, 1280, 720);

    qreal borderWidth = 30;
    dXY = new QPoint(-10, -10);

    QGraphicsRectItem* tBorder = new QGraphicsRectItem(0, 0, scene->width(), borderWidth);
    QGraphicsRectItem* rBorder = new QGraphicsRectItem(scene->width() - borderWidth, 0, borderWidth, scene->height());
    QGraphicsRectItem* bBorder = new QGraphicsRectItem(0, scene->height() - borderWidth, scene->width(), borderWidth);
    QGraphicsRectItem* lBorder = new QGraphicsRectItem(0, 0, borderWidth, scene->height());

    borders = new QList<QGraphicsRectItem*>;
    borders->append(tBorder);
    borders->append(rBorder);
    borders->append(lBorder);
    borders->append(bBorder);

    tBorder->setBrush(QBrush(QColor(66, 66, 66)));
    rBorder->setBrush(QBrush(QColor(66, 66, 66)));
    bBorder->setBrush(QBrush(QColor(66, 66, 66)));
    lBorder->setBrush(QBrush(QColor(66, 66, 66)));

    tree = new QGraphicsPixmapItem(QPixmap::fromImage(QImage(":/AppleTree.png")).scaledToHeight(300));
    tree->setFlags(QGraphicsItem::ItemIsMovable);
    tree->setPos(scene->width()/2, scene->height()/2);

    QGraphicsRectItem* leftWing = new QGraphicsRectItem(0, 0, 5, 50);
    leftWing->setRotation(135);

    QGraphicsRectItem* rightWing = new QGraphicsRectItem(0, 0, 5, 50);
    rightWing->setRotation(-135);

    scene->addItem(tBorder);
    scene->addItem(rBorder);
    scene->addItem(lBorder);
    scene->addItem(bBorder);

    scene->addItem(tree);

    scene->addItem(leftWing);
    scene->addItem(rightWing);

    QList<QGraphicsItem*> wings;
    wings.append(leftWing);
    wings.append(rightWing);

    bird =  scene->createItemGroup(wings);
    bird->setPos(scene->width()/2, scene->height()/2);
    bird->setFlag(QGraphicsItem::ItemIsMovable);

    QTimer* mainTimer = new QTimer();
    mainTimer->setInterval(16);
    mainTimer->setSingleShot(false);
    connect(mainTimer, SIGNAL(timeout()), this, SLOT(moveAndCheck()));
    mainTimer->start();

    QTimer* resizeTimer = new QTimer();
    resizeTimer->setInterval(0);
    resizeTimer->setSingleShot(true);
    connect(resizeTimer, SIGNAL(timeout()), this, SLOT(resizeTrigger()));
    resizeTimer->start();
}

void MainWindow::resizeTrigger() {
    emit resizeEvent(new QResizeEvent(this->size(), this->size()));
}

void MainWindow::moveAndCheck() {
    bird->moveBy(dXY->x(), dXY->y());

    if (bird->collidesWithItem(borders->at(0)) || bird->collidesWithItem(borders->at(3))) {
        dXY->setY(dXY->y() * -1);
    }

    if (bird->collidesWithItem(borders->at(1)) || bird->collidesWithItem(borders->at(2))) {
        dXY->setX(dXY->x() * -1);
    }

    if (bird->collidesWithItem(tree)) {
        dXY = new QPoint(dXY->x() * -1, dXY->y() * -1);
    }
}

void MainWindow::resizeEvent(QResizeEvent *) {
    QRectF bounds = ui->graphicsView->scene()->itemsBoundingRect();
    ui->graphicsView->fitInView(bounds, Qt::KeepAspectRatio);
    ui->graphicsView->centerOn(0, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
