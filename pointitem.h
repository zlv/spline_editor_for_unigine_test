#ifndef POINTITEM_H
#define POINTITEM_H

#include <QGraphicsEllipseItem>

class PointItem : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    explicit PointItem(const QPointF& point, int index);

signals:

public slots:

private:
    int index_;
};

#endif // POINTITEM_H
