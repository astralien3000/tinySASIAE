#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "robot.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Robot& robot, QWidget *parent = 0);
    ~MainWindow();

public slots:
    void update();

private:
    Ui::MainWindow *ui;
    Robot _robot;
};

#endif // MAINWINDOW_H
