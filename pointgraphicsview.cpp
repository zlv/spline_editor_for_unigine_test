#include "pointgraphicsview.h"
#include "pointgraphicsscene.h"
#include <QMouseEvent>

PointGraphicsView::PointGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    QGraphicsScene *scene = new PointGraphicsScene(this);
    QRectF rectan(rect());
    scene->setSceneRect(rectan);
    setScene(scene);
}
