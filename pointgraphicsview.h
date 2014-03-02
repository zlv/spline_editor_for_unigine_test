/*
 * do almost nothing
 * copyright (c) Evgenii Lezhnin <zlvlezhnin@gmail.com>, 2014
 */
#ifndef POINTGRAPHICSVIEW_H
#define POINTGRAPHICSVIEW_H

#include <QGraphicsView>

class PointGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit PointGraphicsView(QWidget *parent = 0);
signals:

public slots:

};

#endif // POINTGRAPHICSVIEW_H
