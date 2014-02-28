#include "splineitem.h"
#include <QPainter>

SplineItem::SplineItem(const QList<QGraphicsItem*>& item_list, QGraphicsItem *parent) : QGraphicsItem(parent), item_list_(item_list)
{
    if (!item_list_.empty()) {
        QList<QGraphicsItem*>::Iterator beg = item_list_.begin();
            double asdf[6];
            int index = 0;
            asdf[index++] = (*beg)->pos().x();
            asdf[index++] = (*beg)->pos().y();
            asdf[index++] = (*beg)->scenePos().x();
            asdf[index++] = (*beg)->scenePos().y();
        boundingRect_ = (*beg)->boundingRect();
        ++beg;
        for (; beg!=item_list_.end(); ++beg) {
            QRectF boundingRectTemp = (*beg)->boundingRect();
            boundingRect_ = boundingRect_.unite(boundingRectTemp);
        }
    }
}

QRectF SplineItem::boundingRect() const
{
    return boundingRect_;
}

void SplineItem::paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!item_list_.empty()) {
        QList<QGraphicsItem*>::Iterator beg = item_list_.begin();
        QPointF lastPoint = (*beg)->pos();
        ++beg;
        for (; beg!=item_list_.end(); ++beg) {
            double asdf[6];
            int index = 0;
            asdf[index++] = lastPoint.x();
            asdf[index++] = lastPoint.y();
            asdf[index++] = (*beg)->pos().x();
            asdf[index++] = (*beg)->pos().y();
            asdf[index++] = (*beg)->scenePos().x();
            asdf[index++] = (*beg)->scenePos().y();
            QPointF point = (*beg)->pos();
            p->drawLine(lastPoint,point);
            lastPoint = point;
        }
    }
}
