#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <cmath>

MainWindow::MainWindow(Robot& robot, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _robot(robot)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&_scene);
    ui->graphicsView->scale(1, -1);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::renderRobot() {

  QPointF pos(_robot.x, _robot.y);
  QPointF dir = QPointF(cos(_robot.angle), sin(_robot.angle));
  QPointF nor = QPointF(cos(_robot.angle + M_PI/2), sin(_robot.angle + M_PI/2));

  QPolygonF bot;
  double scale = 10;
  bot.append(pos - nor * scale);
  bot.append(pos + dir * scale);
  bot.append(pos + nor * scale);

  QPointF wheel_size(0.5, 1.5);
  wheel_size *= scale;

  QPolygonF right_wheel;
  QPointF right_wheel_center = pos + nor * (_robot.width / 2);
  right_wheel.append(right_wheel_center + wheel_size.x() * nor + wheel_size.y() * dir);
  right_wheel.append(right_wheel_center - wheel_size.x() * nor + wheel_size.y() * dir);
  right_wheel.append(right_wheel_center - wheel_size.x() * nor - wheel_size.y() * dir);
  right_wheel.append(right_wheel_center + wheel_size.x() * nor - wheel_size.y() * dir);

  QPolygonF left_wheel;
  QPointF left_wheel_center = pos - nor * (_robot.width / 2);
  left_wheel.append(left_wheel_center + wheel_size.x() * nor + wheel_size.y() * dir);
  left_wheel.append(left_wheel_center - wheel_size.x() * nor + wheel_size.y() * dir);
  left_wheel.append(left_wheel_center - wheel_size.x() * nor - wheel_size.y() * dir);
  left_wheel.append(left_wheel_center + wheel_size.x() * nor - wheel_size.y() * dir);

  _scene.addPolygon(bot);
  _scene.addPolygon(right_wheel);
  _scene.addPolygon(left_wheel);
}

void MainWindow::renderWorld() {

  _scene.addLine(5,5,-5,-5);
  _scene.addLine(5,-5,-5,5);

  QPen grey_pen(QColor(175, 175, 175));

  const int MIN = -200;
  const int MAX = 200;
  const int STEP = 50;
  for(int i = MIN ; i <= MAX ; i += STEP) {
    _scene.addLine(i, MIN, i, MAX, grey_pen);
    _scene.addLine(MIN, i, MAX, i, grey_pen);
  }

  QPen borders_pen(QColor(0,0,0));
  borders_pen.setWidth(2);
  _scene.addLine(MIN, MIN, MIN, MAX, borders_pen);
  _scene.addLine(MIN, MIN, MAX, MIN, borders_pen);
  _scene.addLine(MAX, MIN, MAX, MAX, borders_pen);
  _scene.addLine(MIN, MAX, MAX, MAX, borders_pen);
}

void MainWindow::update()
{
    QMainWindow::update();
    renderWorld();
    renderRobot();

    ui->widthLabel->setText(QString("Width: %1").arg(_robot.width));
    ui->xLabel->setText(QString("X: %1").arg(_robot.x));
    ui->yLabel->setText(QString("Y: %1").arg(_robot.y));
    ui->angleLabel->setText(QString("Angle: %1").arg(_robot.angle));
    ui->leftSpeedLabel->setText(QString("Left speed: %1").arg(_robot.left_speed));
    ui->rightSpeedLabel->setText(QString("Right speed: %1").arg(_robot.right_speed));
    ui->leftEncLabel->setText(QString("Left enc: %1").arg(_robot.left_encoder));
    ui->rightEncLabel->setText(QString("Right enc: %1").arg(_robot.right_encoder));
}
