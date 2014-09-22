#include "mainwindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Robot r;
    MainWindow w(r);
    w.show();
    w.update();
    return a.exec();
}
