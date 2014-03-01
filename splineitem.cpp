#include "splineitem.h"
#include "pointitem.h"
#include "spline.h"
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
    QRectF realBound = boundingRect_;
    realBound.setTopLeft(realBound.topLeft()-QPointF(50,50));
    realBound.setBottomRight(realBound.bottomRight()+QPointF(50,50));
    return realBound;
}

void SplineItem::paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!item_list_.empty()) {
        QPointF lastPoint;
        bool bLastAndNextPointSpec = 0;
        QPointF nextPoint;
        QList<QGraphicsItem*>::Iterator beg = item_list_.begin();
        for (; beg!=item_list_.end();) {
            if ((*beg)->type()==PointItem::Type) {
                QPointF point;
                QPen pen;
                if (!bLastAndNextPointSpec) {
                    point = static_cast<PointItem*>(*beg)->mapRectToParent(static_cast<PointItem*>(*beg)->rect()).center();
                }
                else {
                    point = nextPoint;
                    pen.setStyle(Qt::DotLine);
                    p->setPen(pen);
                    p->drawLine(lastPoint,point);
                }
                pen.setStyle(Qt::SolidLine);
                p->setPen(pen);
                QList<QGraphicsItem*>::Iterator cur_beg = beg;
                do {
                    ++beg;
                    if (beg==item_list_.end())
                        break;
                } while ((*beg)->type()!=PointItem::Type);
                if (beg==item_list_.end()) 
                    break;
                nextPoint = static_cast<PointItem*>(*beg)->mapRectToParent(static_cast<PointItem*>(*beg)->rect()).center();
                Spline spline(lastPoint,point,nextPoint,static_cast<PointItem*>(*cur_beg),static_cast<PointItem*>(*beg));
                QList<QPointF> point_list = spline.getPoints();
                QList<QPointF>::Iterator point_list_iter = point_list.begin();
                QPointF last_spline_point = *point_list_iter;
                ++point_list_iter;
                for (; point_list_iter!=point_list.end(); ++point_list_iter) {
                    p->drawLine(last_spline_point, *point_list_iter);
                    last_spline_point = *point_list_iter;
                }

                lastPoint = point;
                bLastAndNextPointSpec = 1;
            }
            else {
                ++beg;
            }
        }
    }
}
