#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene* scene = new QGraphicsScene;

    QLabel* test = new QLabel;
    test->setPixmap(QPixmap::fromImage(QImage(":/AppleTree.png")));

    scene->addWidget(test);
    QPolygon* poly = new QPolygon(QRect(0, 0, 100, 100));
    QBrush brush;
    brush.setColor(Qt::red);
    QPen pen(Qt::green);
    scene->addPolygon(*poly);

    scene->setSceneRect(0, 0, 100, 100);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->adjustSize();
}

void MainWindow::resizeEvent(QResizeEvent *) {
    QRectF bounds = ui->graphicsView->scene()->itemsBoundingRect();
    bounds.setWidth(bounds.width()*0.9);
    bounds.setHeight(bounds.height()*0.9);
    ui->graphicsView->fitInView(bounds, Qt::KeepAspectRatio);
    ui->graphicsView->centerOn(0, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
