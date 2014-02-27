#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pointgraphicsview.h"
#include "pointgraphicsscene.h"
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QHBoxLayout *box = new QHBoxLayout();
    PointGraphicsView *view = new PointGraphicsView(this);
    box->addWidget(view);
    scene_ = static_cast<PointGraphicsScene*>(view->scene());
    ui->dummy_widget->setLayout(box);
    createToolbar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createToolbar() {
    QAction *pointAct = new QAction(tr("&Add Point"),this);
    connect(pointAct,SIGNAL(triggered(bool)),scene_,SLOT(change_point_mode(bool)));
    pointAct->setCheckable(1);
    QToolBar *toolbar = addToolBar(tr("&Add Control Point"));
    toolbar->addAction(pointAct);
    //toolbar->show();
}
