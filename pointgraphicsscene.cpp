#include "pointgraphicsscene.h"
#include "pointitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>

PointGraphicsScene::PointGraphicsScene(QObject *parent) :
    QGraphicsScene(parent), bAdd_else_select_(0), index_(0)
{
    setItemIndexMethod(QGraphicsScene::NoIndex);
    connect(this,SIGNAL(changed(QList<QRectF>)),this,SLOT(updateLines(QList<QRectF>)));
}

void PointGraphicsScene::change_point_mode(bool toggled) {
    bAdd_else_select_ = toggled;
}

/*Добавляем свои точки, содержащие индекс, а также линии (сплайны), содержащие соединяемые индексы*/
void PointGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    if (bAdd_else_select_) {
        PointItem *pointItem = new PointItem(e->scenePos(),index_++);
        pointItem->setFlag(QGraphicsItem::ItemIsMovable,1);
        addItem(pointItem);
    }
}

/*в зависимости от того, куда перемещены точки, строим сплайн*/
void PointGraphicsScene::updateLines(QList<QRectF> rect_list) {
    for (QList<QRectF>::Iterator beg = rect_list.begin(); beg!=rect_list.end(); ++beg) {
        items(*beg);
    }
}
