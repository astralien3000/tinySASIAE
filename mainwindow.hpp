#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "robotbin.hpp"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLinkedList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  void renderRobot(const Robot& robot, QLinkedList<QPointF>& _pointList);
  void renderWorld(void);

  void updateRobotInfos(const Robot& robot);

public slots:
    void update();

private:
    struct InternalRobot {
      const RobotBin* engine;
      QLinkedList<QPointF> _pointList;
    };

    Ui::MainWindow *ui;
    QLinkedList<InternalRobot> _engines;
    QTimer _timer;

    QGraphicsScene _scene;

    static const int POINT_LIST_SIZE = 50;
    static const int ADD_POINT_EVERY = 10;

public:
    void addRobot(RobotBin* bin) {
      InternalRobot e;
      e.engine = bin;
      _engines.append(e);
    }
};

#endif // MAINWINDOW_H
