//copyright (c) Evgenii Lezhnin <zlvlezhnin@gmail.com>, 2014
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
        }
        ++beg;
        for (; beg!=item_list.end(); ++beg) {
            if ((*beg)->type()==PointItem::Type) {
                item_list_.push_back(*beg);
                QRectF boundingRectTemp = (*beg)->boundingRect();
                boundingRect_ = boundingRect_.united((*beg)->mapRectToParent(boundingRectTemp));
            }
        }
        find_splines();
    }
}

QRectF SplineItem::boundingRect() const
{
    QRectF realBound = boundingRect_;
    realBound.setTopLeft(realBound.topLeft()-QPointF(50,50)); //[its a measurement error]
    realBound.setBottomRight(realBound.bottomRight()+QPointF(50,50));
    return realBound;
}

void SplineItem::paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!point_lists_.empty()) {
        QList<QList<QPointF> >::iterator beg = point_lists_.begin();
        for (; beg!=point_lists_.end(); ++beg) {
            QPen pen;
            pen.setStyle(Qt::SolidLine);
            p->setPen(pen);
            QList<QPointF>::Iterator point_list_iter = (*beg).begin();
            QPointF first_point;
            first_point = *point_list_iter;
            QPointF last_spline_point = first_point;
            ++point_list_iter;
            for (; point_list_iter!=(*beg).end(); ++point_list_iter) {
                p->drawLine(last_spline_point, *point_list_iter);
                last_spline_point = *point_list_iter;
            }
            //only a straight line
            pen.setStyle(Qt::DotLine);
            p->setPen(pen);
            p->drawLine(first_point,last_spline_point);
        }
    }
}

void SplineItem::find_splines()
{
    if (!item_list_.empty()) {
        vector<QPointF> point_vec; //преобразованные точки
        QList<QGraphicsItem*>::iterator beg = item_list_.begin();
        for (; beg!=item_list_.end(); ++beg) {
            point_vec.push_back((*beg)->mapRectToParent(static_cast<PointItem*>(*beg)->rect()).center());
        }
        beg = item_list_.begin();
        for (int i=0; beg!=item_list_.end(); i++) {
            QList<QGraphicsItem*>::iterator cur_beg = beg;
            ++beg;
            if (beg==item_list_.end())
                break;
            int lastPoint_i = i<=0?i:i-1;
            int nextPoint_i = i+1>item_list_.size()-1?i:i+1;
            int nextnextPoint_i = i+2>item_list_.size()-1?i:i+2;
            Spline spline(point_vec[lastPoint_i],point_vec[i],point_vec[nextPoint_i],point_vec[nextnextPoint_i],static_cast<PointItem*>(*cur_beg),static_cast<PointItem*>(*beg));
            point_lists_.push_back(spline.getPoints());
        }
    }
}
