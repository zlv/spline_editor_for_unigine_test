//copyright (c) Evgenii Lezhnin <zlvlezhnin@gmail.com>, 2014
#include "pointgraphicsview.h"
#include "pointgraphicsscene.h"
#include "mainwindow.h"
#include <QMouseEvent>

PointGraphicsView::PointGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    PointGraphicsScene *scene = new PointGraphicsScene(parent);
    QRectF rectan(rect());
    scene->setSceneRect(rectan);
    setScene(scene);
    connect(scene,SIGNAL(changeSettings(PointItem*)),static_cast<MainWindow*>(parent),SLOT(changeSettings_slot(PointItem*)));
}
