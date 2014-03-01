#include "splineitem.h"
#include "pointitem.h"
#include <QPainter>

SplineItem::SplineItem(const QList<QGraphicsItem*>& item_list, QGraphicsItem *parent) : QGraphicsItem(parent), item_list_(item_list)
{
    if (!item_list_.empty()) {
        QList<QGraphicsItem*>::Iterator beg = item_list_.begin();
        boundingRect_ = static_cast<PointItem*>(*beg)->mapRectToParent((*beg)->boundingRect());
        ++beg;
        for (; beg!=item_list_.end(); ++beg) {
            QRectF boundingRectTemp = (*beg)->boundingRect();
            boundingRect_ = boundingRect_.unite(static_cast<PointItem*>(*beg)->mapRectToParent(boundingRectTemp));
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
        QPointF lastPoint;
        bool bLastPointSpec = 0;
        QList<QGraphicsItem*>::Iterator beg = item_list_.begin();
        for (; beg!=item_list_.end(); ++beg) {
            if ((*beg)->type()==PointItem::Type) {
                QPointF point = static_cast<PointItem*>(*beg)->mapRectToParent(static_cast<PointItem*>(*beg)->rect()).center();
                if (bLastPointSpec) {
                    p->drawLine(lastPoint,point);
                }
                lastPoint = point;
                bLastPointSpec = 1;
            }
        }
    }
}
