#include "mainwindow.hpp"
#include <QApplication>

#include <cmath>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Robot r;
    r.width = 50;
    r.angle = M_PI / 4;
    r.y = 100;

    MainWindow w(r);
    w.show();
    w.update();
    return a.exec();
}
