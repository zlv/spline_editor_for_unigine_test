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
    connect(ui->applyButton,SIGNAL(clicked()),this,SLOT(apply()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeSettings_slot(PointItem *p)
{
    if (lastPointItem_)
        disconnect(lastPointItem_,SLOT(setParams_slot(double[])));
    ui->bias_edit->setValue(p->bias());
    ui->cont_edit->setValue(p->continuity());
    ui->tens_edit->setValue(p->tension());
    connect(this,SIGNAL(setParams(double[])),p,SLOT(setParams_slot(double[])));
    lastPointItem_ = p;
}

void MainWindow::apply()
{
    double par[3];
    par[0] = ui->bias_edit->value();
    par[1] = ui->cont_edit->value();
    par[2] = ui->tens_edit->value();
    setParams(par);
}

void MainWindow::createToolbar() {
    QAction *pointAct = new QAction(tr("&Add Point"),this);
    connect(pointAct,SIGNAL(triggered(bool)),scene_,SLOT(change_point_mode(bool)));
    pointAct->setCheckable(1);
    QToolBar *toolbar = addToolBar(tr("&Add Control Point"));
    toolbar->addAction(pointAct);
    //toolbar->show();
}
