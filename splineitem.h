#ifndef SPLINEITEM_H
#define SPLINEITEM_H

#include <QGraphicsItem>

class SplineItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:

    explicit SplineItem(const QList<QGraphicsItem*>&,QGraphicsItem *parent = 0);
    int type() const {
       // Enable the use of qgraphicsitem_cast with this item.
       return Type;
    }
protected:
    QRectF boundingRect() const;
    void paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *);

signals:

public slots:

private:
    QList<QGraphicsItem*> item_list_;
    QRectF boundingRect_;

public:
    enum { Type = UserType + 2 };
};

#endif // SPLINEITEM_H
