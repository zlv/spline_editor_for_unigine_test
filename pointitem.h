#ifndef POINTITEM_H
#define POINTITEM_H

#include <QGraphicsEllipseItem>

class PointItem : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:

    explicit PointItem(const QPointF& point, int index);
    int type() const {
       // Enable the use of qgraphicsitem_cast with this item.
       return Type;
    }
    double bias() {return param_[0];}
    double continuity() {return param_[1];}
    double tension() {return param_[2];}

signals:

public slots:
    void setParams_slot(double[]);

private:
    int index_;
    double param_[3];

public:
    enum { Type = UserType + 1 };
};

#endif // POINTITEM_H
