/*
 * point on a scene to set parameters of a spline
 * copyright (c) Evgenii Lezhnin <zlvlezhnin@gmail.com>, 2014
 */
#ifndef POINTITEM_H
#define POINTITEM_H

#include <QGraphicsEllipseItem>

class PointItem : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:

    explicit PointItem(const QPointF& point);
    int type() const {
       // Enable the use of qgraphicsitem_cast with this item.
       return Type;
    }
    double bias() const {return param_[0];}
    double continuity() const {return param_[1];}
    double tension() const {return param_[2];}
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value); //tracks changes of a position
signals:
public slots:
    void setParams_slot(double,double,double);

private:
    double param_[3];

public:
    enum { Type = UserType + 1 };
};

#endif // POINTITEM_H
