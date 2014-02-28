#ifndef POINTGRAPHICSSCENE_H
#define POINTGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <list>
using namespace std;

class PointItem;

class PointGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit PointGraphicsScene(QObject *parent = 0);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    void changeSettings(PointItem*);
private slots:
    void selectionChanged_slot();
public slots:
    void change_point_mode(bool);
    void updateLines();

private:
    bool bAdd_else_select_;
    int index_;
};

#endif // POINTGRAPHICSSCENE_H
