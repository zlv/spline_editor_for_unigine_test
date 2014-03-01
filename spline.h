#ifndef SPLINE_H
#define SPLINE_H

#include <QList>
#include <QPointF>
class PointItem;
class Spline
{
public:
    Spline(const QPointF&,const QPointF&,const QPointF&,const PointItem*, const PointItem *nextpoint);
    QList<QPointF> getPoints();

private:
    QPointF cur_, next_;
    QPointF d1_, d2_;
    bool bSplineBuilded;
    QList<QPointF> list_;
};

#endif // SPLINE_H
