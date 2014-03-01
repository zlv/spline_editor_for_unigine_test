#include "pointgraphicsscene.h"
#include "pointitem.h"
#include "splineitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>
#include <QKeyEvent>

PointGraphicsScene::PointGraphicsScene(QObject *parent) :
    QGraphicsScene(parent), bAdd_else_select_(0), index_(0)
{
    setItemIndexMethod(QGraphicsScene::NoIndex);
    //connect(this,SIGNAL(changed(QList<QRectF>)),this,SLOT(changed_slot(QList<QRectF>)));
    connect(this,SIGNAL(selectionChanged()),this,SLOT(selectionChanged_slot()));
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
        pointItem->setFlag(QGraphicsItem::ItemIsSelectable,1);
        pointItem->setFlag(QGraphicsItem::ItemSendsGeometryChanges,1);
        addItem(pointItem);
    }
}

void PointGraphicsScene::keyPressEvent(QKeyEvent *keyEvent)
{
    if (keyEvent->key()==Qt::Key_Delete) {
        QList<QGraphicsItem*> item_list = selectedItems();
        for (QList<QGraphicsItem*>::Iterator beg = item_list.begin(); beg!=item_list.end(); ++beg) {
            removeItem(*beg);
        }
    }
}

void PointGraphicsScene::removeSpline()
{
    QList<QGraphicsItem*> item_list = items();
    for (QList<QGraphicsItem*>::Iterator beg = item_list.begin(); beg!=item_list.end(); ++beg) {
        if ((*beg)->type()==SplineItem::Type) {
            removeItem(*beg);
            break;
        }
    }
}

void PointGraphicsScene::selectionChanged_slot()
{
    QList<QGraphicsItem*> item_list = selectedItems();
    for (QList<QGraphicsItem*>::Iterator beg = item_list.begin(); beg!=item_list.end(); ++beg) {
        if ((*beg)->type()==PointItem::Type) {
            changeSettings(static_cast<PointItem*>(*beg));
            break;
        }
    }
}

void PointGraphicsScene::changed_slot(QList<QRectF>)
{
    removeSpline();
}

/*в зависимости от того, куда перемещены точки, строим сплайн*/
void PointGraphicsScene::updateLines() {
    QList<QGraphicsItem*> item_list = items();
    for (QList<QGraphicsItem*>::Iterator beg = item_list.begin(); beg!=item_list.end(); ++beg) {
        if ((*beg)->type()==SplineItem::Type) {
            removeItem(*beg);
            break;
        }
    }
    SplineItem *spline = new SplineItem(item_list);
    addItem(spline);
}
