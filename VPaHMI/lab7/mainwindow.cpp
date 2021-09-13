#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QGraphicsProxyWidget>
#include <QDialog>
#include <QSpinBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene* scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0, 0, 738, 450);

    QLabel* test = new QLabel;
    test->setPixmap(QPixmap::fromImage(QImage(":/AppleTree.png")).scaledToHeight(300));

    QGraphicsProxyWidget* temp = scene->addWidget(test);
    elements.insert("tree", temp);
    qDebug() << elements["tree"]->rect();
    elements["tree"]->setPos(-245, -122);
//    QPolygon* poly = new QPolygon(QRect(0, 0, 100, 100));
//    QBrush brush;
//    brush.setColor(Qt::red);
//    QPen pen(Qt::green);
//    scene->addPolygon(*poly);


    ui->graphicsView->adjustSize();
}

void MainWindow::resizeEvent(QResizeEvent *) {
//    QRectF bounds = ui->graphicsView->scene()->itemsBoundingRect();
//    bounds.setWidth(bounds.width()*0.9);
//    bounds.setHeight(bounds.height()*0.9);
//    ui->graphicsView->fitInView(bounds, Qt::KeepAspectRatio);
//    ui->graphicsView->centerOn(0, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnTestPost_clicked()
{
    QDialog* dlg = new QDialog();

    QSpinBox* m_ptxtFirstName = new QSpinBox;
    QSpinBox* m_ptxtLastName = new QSpinBox;
    m_ptxtFirstName->setRange(-10e3, 10e3);
    m_ptxtLastName->setRange(-10e3, 10e3);

    QLabel* plblFirstName = new QLabel("&X");
    QLabel* plblLastName = new QLabel("&Y");

    plblFirstName->setBuddy(m_ptxtFirstName);
    plblLastName->setBuddy(m_ptxtLastName);

    QPushButton* pcmdOk = new QPushButton("&Ok");
    QPushButton* pcmdCancel = new QPushButton("&Cancel");

    connect(pcmdOk, SIGNAL(clicked()), dlg, SLOT(accept()));
    connect(pcmdCancel, SIGNAL(clicked()), dlg, SLOT(reject()));

    QGridLayout* ptopLayout = new QGridLayout;
    ptopLayout->addWidget(plblFirstName, 0, 0);
    ptopLayout->addWidget(plblLastName, 1, 0);
    ptopLayout->addWidget(m_ptxtFirstName, 0, 1);
    ptopLayout->addWidget(m_ptxtLastName, 1, 1);
    ptopLayout->addWidget(pcmdOk, 2, 0);
    ptopLayout->addWidget(pcmdCancel, 2, 1);
    dlg->setLayout(ptopLayout);
    if (dlg->exec() == QDialog::Accepted) {
        elements["tree"]->setPos(m_ptxtFirstName->value(), m_ptxtLastName->value());
    }
}
