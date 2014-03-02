/*
 * Scene redefinition, that adds Points and Splines.
 * copyright (c) Evgenii Lezhnin <zlvlezhnin@gmail.com>, 2014
 */
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
    void changeSettings(PointItem*); //emits then sellection changes, this signal is connected to function in Main Window
private slots:
    void selectionChanged_slot(); //connected to standart signal of QGraphicsScene
public slots:
    void change_point_mode(bool); //add or other
    void updateLines(); //build new spline

private:
    bool bAdd_; //add or other
};

#endif // POINTGRAPHICSSCENE_H
