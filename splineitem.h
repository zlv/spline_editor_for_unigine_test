/*
 * Graphic realization of a spline
 * copyright (c) Evgenii Lezhnin <zlvlezhnin@gmail.com>, 2014
 */
#ifndef SPLINEITEM_H
#define SPLINEITEM_H

#include <QGraphicsItem>

class SplineItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:

    explicit SplineItem(const QList<QGraphicsItem*>&,QGraphicsItem *parent = 0); //find a bounding rect, also form the list of point items, and finally find all spline points
    int type() const {
       // Enable the use of qgraphicsitem_cast with this item.
       return Type;
    }
protected:
    QRectF boundingRect() const;
    void paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *); //draw splines and straight lines, which connects points
private:
    void find_splines(); //find spline points (point_lists_)
signals:
public slots:

private:
    QList<QGraphicsItem*> item_list_;
    QList<QList<QPointF> > point_lists_;
    QRectF boundingRect_;

public:
    enum { Type = UserType + 2 };
};

#endif // SPLINEITEM_H
