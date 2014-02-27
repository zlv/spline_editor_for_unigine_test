#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class PointGraphicsScene;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void createToolbar();

private:
    Ui::MainWindow *ui;
    PointGraphicsScene *scene_;
};

#endif // MAINWINDOW_H
