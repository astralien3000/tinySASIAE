#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <cmath>

#include <QTreeWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&_scene);
    ui->graphicsView->scale(1, 1);

    _timer.connect(&_timer, SIGNAL(timeout()), this, SLOT(update()));
    _timer.setInterval(1000.0 / 60.0);
    _timer.start();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::renderRobot(const Robot& robot, QLinkedList<QPointF>& _pointList) {

  QPointF pos(robot.x, robot.y);
  QPointF dir = QPointF(cos(robot.angle), sin(robot.angle));
  QPointF nor = QPointF(cos(robot.angle + M_PI/2), sin(robot.angle + M_PI/2));

  QPolygonF bot;
  double scale = 10;
  bot.append(pos - nor * scale);
  bot.append(pos + dir * scale);
  bot.append(pos + nor * scale);

  QPointF wheel_size(0.5, 1.5);
  wheel_size *= scale;

  QPolygonF right_wheel;
  QPointF right_wheel_center = pos + nor * (robot.width / 2);
  right_wheel.append(right_wheel_center + wheel_size.x() * nor + wheel_size.y() * dir);
  right_wheel.append(right_wheel_center - wheel_size.x() * nor + wheel_size.y() * dir);
  right_wheel.append(right_wheel_center - wheel_size.x() * nor - wheel_size.y() * dir);
  right_wheel.append(right_wheel_center + wheel_size.x() * nor - wheel_size.y() * dir);

  QPolygonF left_wheel;
  QPointF left_wheel_center = pos - nor * (robot.width / 2);
  left_wheel.append(left_wheel_center + wheel_size.x() * nor + wheel_size.y() * dir);
  left_wheel.append(left_wheel_center - wheel_size.x() * nor + wheel_size.y() * dir);
  left_wheel.append(left_wheel_center - wheel_size.x() * nor - wheel_size.y() * dir);
  left_wheel.append(left_wheel_center + wheel_size.x() * nor - wheel_size.y() * dir);

  _scene.addPolygon(bot);
  _scene.addPolygon(right_wheel);
  _scene.addPolygon(left_wheel);

  const QPointF* prev = NULL;
  int j = 0;
  for(QLinkedList<QPointF>::Iterator i = _pointList.begin(); i != _pointList.end(); i++, j++) {
      if(prev) {
          QLine line((int) prev->x(), (int) prev->y(), (int) (*i).x(), (int) (*i).y());
          QPen pen(QBrush(QColor(255, 0, 0, 255 - (255. / POINT_LIST_SIZE * j))), 3);
          _scene.addLine(line, pen);
      }
      prev = &(*i);
  }

  static int cpt = 0;
  if(++cpt > ADD_POINT_EVERY) {
      cpt = 0;
      _pointList.prepend(pos);
  }

  while(_pointList.size() > POINT_LIST_SIZE) {
      _pointList.removeLast();
  }
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

void MainWindow::updateRobotInfos(const Robot& robot, const QString& name) {
  double display_angle = fmod(robot.angle * 180.0 / M_PI, 360);
  if(display_angle < 0.0) display_angle += 360.0;

  QTreeWidgetItem* item = NULL;

  QList<QTreeWidgetItem*> items = ui->treeWidget->findItems(name, Qt::MatchExactly);
  if(items.empty()) {
    item = new QTreeWidgetItem(QStringList(name));
    ui->treeWidget->addTopLevelItem(item);
    item->setExpanded(true);
    item->setFirstColumnSpanned(true);
    item->addChild(new QTreeWidgetItem(QStringList{"width", QString("%1").arg(robot.width)}));
    item->addChild(new QTreeWidgetItem(QStringList{"x", QString("%1").arg(robot.x)}));
    item->addChild(new QTreeWidgetItem(QStringList{"y", QString("%1").arg(robot.y)}));
    item->addChild(new QTreeWidgetItem(QStringList{"angle", QString("%1").arg(display_angle)}));
    item->addChild(new QTreeWidgetItem(QStringList{"left speed", QString("%1").arg(robot.left_speed)}));
    item->addChild(new QTreeWidgetItem(QStringList{"right speed", QString("%1").arg(robot.right_speed)}));
    item->addChild(new QTreeWidgetItem(QStringList{"left encoder", QString("%1").arg(robot.left_encoder)}));
    item->addChild(new QTreeWidgetItem(QStringList{"right encoder", QString("%1").arg(robot.right_encoder)}));
  }
  else {
    item = items[0];
    for(int i = 0 ; i < item->childCount() ; i++) {
      QTreeWidgetItem* child = item->child(i);
      if(child->text(0) == "width") child->setText(1, QString("%1").arg(robot.width));
      if(child->text(0) == "x") child->setText(1, QString("%1").arg(robot.x));
      if(child->text(0) == "y") child->setText(1, QString("%1").arg(robot.y));
      if(child->text(0) == "angle") child->setText(1, QString("%1").arg(display_angle));
      if(child->text(0) == "left speed") child->setText(1, QString("%1").arg(robot.left_speed));
      if(child->text(0) == "right speed") child->setText(1, QString("%1").arg(robot.right_speed));
      if(child->text(0) == "left encoder") child->setText(1, QString("%1").arg(robot.left_encoder));
      if(child->text(0) == "right encoder") child->setText(1, QString("%1").arg(robot.right_encoder));
    }
  }
}

void MainWindow::update()
{
    QMainWindow::update();
    _scene.clear();
    renderWorld();

    for(QLinkedList<InternalRobot>::Iterator it = _engines.begin() ; it != _engines.end() ; it++) {
      if(it->engine) {
        renderRobot(it->engine->getRobot(), it->_pointList);
        updateRobotInfos(it->engine->getRobot(), it->name);
      }
    }
}
