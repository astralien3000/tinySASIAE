#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "robot.hpp"
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Robot& robot, QWidget *parent = 0);
    ~MainWindow();

  void renderRobot(void);

public slots:
    void update();

private:
    Ui::MainWindow *ui;
    Robot& _robot;

    QGraphicsScene _scene;
};

#endif // MAINWINDOW_H
