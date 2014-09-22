#include "mainwindow.hpp"
#include <QApplication>
#include <QTimer>

#include <cmath>
#include "physicsengine.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Robot r;
    r.width = 50;

    PhysicsEngine engine(r);

    QTimer timer;
    timer.setInterval(1000.0 / 60.0);

    MainWindow w(r);
    w.show();
    w.update();


    timer.connect(&timer, SIGNAL(timeout()), &engine, SLOT(update()));
    timer.connect(&timer, SIGNAL(timeout()), &w, SLOT(update()));

    timer.start();

    return a.exec();
}
