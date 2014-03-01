#include "splineitem.h"
#include "pointitem.h"
#include "spline.h"
#include <QPainter>
#include <vector>
using namespace std;

SplineItem::SplineItem(const QList<QGraphicsItem*>& item_list, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    if (!item_list.empty()) {
            QList<QGraphicsItem*>::const_iterator beg = item_list.begin();
            if ((*beg)->type()==PointItem::Type) {
                boundingRect_ = (*beg)->mapRectToParent((*beg)->boundingRect());
                item_list_.push_back(*beg);
                ++beg;
                for (; beg!=item_list.end(); ++beg) {
                    if ((*beg)->type()==PointItem::Type) {
                        item_list_.push_back(*beg);
                        QRectF boundingRectTemp = (*beg)->boundingRect();
                        boundingRect_ = boundingRect_.unite((*beg)->mapRectToParent(boundingRectTemp));
                    }
                }
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
        vector<QPointF> point_vec; //преобразованные точки
        QList<QGraphicsItem*>::iterator beg = item_list_.begin();
        for (; beg!=item_list_.end(); ++beg) {
            point_vec.push_back(static_cast<PointItem*>(*beg)->mapRectToParent(static_cast<PointItem*>(*beg)->rect()).center());
        }
        beg = item_list_.begin();
        for (int i=0; beg!=item_list_.end();i++) {
            QPen pen;
            if (i>0) {
                pen.setStyle(Qt::DotLine);
                p->setPen(pen);
                p->drawLine(point_vec[i-1],point_vec[i]);
            }
            pen.setStyle(Qt::SolidLine);
            p->setPen(pen);
            QList<QGraphicsItem*>::iterator cur_beg = beg;
            ++beg;
            if (beg==item_list_.end())
                break;
            int lastPoint_i = i<=0?i:i-1;
            int nextPoint_i = i+1>item_list_.size()-1?i:i+1;
            int nextnextPoint_i = i+2>item_list_.size()-1?i:i+2;
            Spline spline(point_vec[lastPoint_i],point_vec[i],point_vec[nextPoint_i],point_vec[nextnextPoint_i],static_cast<PointItem*>(*cur_beg),static_cast<PointItem*>(*beg));
            QList<QPointF> point_list = spline.getPoints();
            QList<QPointF>::Iterator point_list_iter = point_list.begin();
            QPointF last_spline_point = *point_list_iter;
            ++point_list_iter;
            for (; point_list_iter!=point_list.end(); ++point_list_iter) {
                p->drawLine(last_spline_point, *point_list_iter);
                last_spline_point = *point_list_iter;
            }
        }
    }
}
