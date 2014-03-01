#include "pointitem.h"
#include "pointgraphicsscene.h"
#include <QBrush>

PointItem::PointItem(const QPointF& point, int index) :
    QGraphicsEllipseItem(point.x(),point.y(),8,8), index_(index) {
    setBrush(Qt::red);
    for (int i=0; i<3; i++)
        param_[i] = 0;
}

QVariant PointItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change==QGraphicsItem::ItemPositionChange) {
        static_cast<PointGraphicsScene*>(scene())->removeSpline();
    }
    return QGraphicsEllipseItem::itemChange(change,value);
}

void PointItem::setParams_slot(double bias, double cont, double tens) {
    param_[0] = bias;
    param_[1] = cont;
    param_[2] = tens;
}
