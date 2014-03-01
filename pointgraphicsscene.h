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
    void removeSpline();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *keyEvent);
private:
signals:
    void changeSettings(PointItem*);
private slots:
    void selectionChanged_slot();
    void changed_slot(QList<QRectF>);
public slots:
    void change_point_mode(bool);
    void updateLines();

private:
    bool bAdd_else_select_;
    int index_;
};

#endif // POINTGRAPHICSSCENE_H
