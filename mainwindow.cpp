//copyright (c) Evgenii Lezhnin <zlvlezhnin@gmail.com>, 2014
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pointgraphicsview.h"
#include "pointgraphicsscene.h"
#include "pointitem.h"
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), lastPointItem_(NULL)
{
    ui->setupUi(this);
    QHBoxLayout *box = new QHBoxLayout();
    PointGraphicsView *view = new PointGraphicsView(this);
    box->addWidget(view);
    scene_ = static_cast<PointGraphicsScene*>(view->scene());
    ui->dummy_widget->setLayout(box);
    createToolbar();
    connect(ui->drawButton,SIGNAL(clicked()),this,SLOT(apply()));
    connect(ui->drawButton,SIGNAL(clicked()),scene_,SLOT(updateLines()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeSettings_slot(PointItem *p)
{
    if (lastPointItem_) {
        apply();
        disconnect(lastPointItem_,SLOT(setParams_slot(double,double,double)));
    }
    ui->bias_edit->setEnabled(1);
    ui->cont_edit->setEnabled(1);
    ui->tens_edit->setEnabled(1);
    ui->bias_edit->setValue(p->bias());
    ui->cont_edit->setValue(p->continuity());
    ui->tens_edit->setValue(p->tension());
    connect(this,SIGNAL(setParams(double,double,double)),p,SLOT(setParams_slot(double,double,double)));
    lastPointItem_ = p;
}

void MainWindow::apply()
{
    setParams(ui->bias_edit->value(),ui->cont_edit->value(),ui->tens_edit->value());
}

void MainWindow::createToolbar() {
    QAction *pointAct = new QAction(tr("&Add Point"),this);
    connect(pointAct,SIGNAL(triggered(bool)),scene_,SLOT(change_point_mode(bool)));
    pointAct->setCheckable(1);
    QToolBar *toolbar = addToolBar(tr("&Add Control Point"));
    toolbar->addAction(pointAct);
}
