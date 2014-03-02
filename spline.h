/*
 * Kochanek-Bartels spline realization
 * copyright (c) Evgenii Lezhnin <zlvlezhnin@gmail.com>, 2014
 */
#ifndef SPLINE_H
#define SPLINE_H

#include <QList>
#include <QPointF>
class PointItem;
class Spline
{
public:
    Spline(const QPointF&,const QPointF&,const QPointF&,const QPointF&,const PointItem*, const PointItem *nextpoint); //save parameters and count tangents
    QList<QPointF> getPoints(); //do interpolation for some amount of points

private:
    QPointF cur_, next_;
    QPointF d1_, d2_; //tangents
    QList<QPointF> list_;
};

#endif // SPLINE_H
