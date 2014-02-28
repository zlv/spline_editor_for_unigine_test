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
    void changeSettings_slot(PointItem*);
    void apply();
signals:
    void setParams(double,double,double);
private:
    void createToolbar();

private:
    Ui::MainWindow *ui;
    PointGraphicsScene *scene_;
    PointItem *lastPointItem_;
};

#endif // MAINWINDOW_H
