//copyright (c) Evgenii Lezhnin <zlvlezhnin@gmail.com>, 2014
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char **argv) {
    QApplication app(argc,argv);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
