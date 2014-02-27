#include "pointitem.h"
#include <QBrush>

PointItem::PointItem(const QPointF& point, int index) :
    QGraphicsEllipseItem(point.x(),point.y(),8,8), index_(index) {
    setBrush(Qt::red);
}
