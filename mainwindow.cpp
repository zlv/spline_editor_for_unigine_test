#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createToolbar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createToolbar() {
    QAction *pointAct = new QAction(tr("&Add Point"),this);
    pointAct->setCheckable(1);
    QToolBar *toolbar = addToolBar(tr("&Add Control Point"));
    toolbar->addAction(pointAct);
    //toolbar->show();
}
