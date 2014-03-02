/*
 * Main window of Kochanek-Bartels Spline Editor. It uses QGraphicsScene classes and standart features for moving, selecting and deleting elements. To select or move element use mouse double click; to delete element press 'delete' key. To add point press 'add point' in menu, and then mouse click.
 * copyright (c) Evgenii Lezhnin <zlvlezhnin@gmail.com>, 2014
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class PointGraphicsScene;
class PointItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void changeSettings_slot(PointItem*); //init text edits
    void apply(); //copy text edits data to a Graphics Item data
signals:
    void setParams(double,double,double); //link to Graphics' Item object function
private:
    void createToolbar(); //'Add Point' button

private:
    Ui::MainWindow *ui;
    PointGraphicsScene *scene_;
    PointItem *lastPointItem_; //last Graphics' Item object, that was used to set data with text edits
};

#endif // MAINWINDOW_H
