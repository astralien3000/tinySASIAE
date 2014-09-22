#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Robot& robot, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _robot(robot)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update()
{
    ui->widthLabel->setText(QString("Width: %1").arg(_robot.width));
    ui->xLabel->setText(QString("X: %1").arg(_robot.x));
    ui->yLabel->setText(QString("Y: %1").arg(_robot.y));
    ui->angleLabel->setText(QString("Angle: %1").arg(_robot.angle));
    ui->leftSpeedLabel->setText(QString("Left speed: %1").arg(_robot.left_speed));
    ui->rightSpeedLabel->setText(QString("Right speed: %1").arg(_robot.right_speed));
    ui->leftEncLabel->setText(QString("Left enc: %1").arg(_robot.left_encoder));
    ui->rightEncLabel->setText(QString("Right enc: %1").arg(_robot.right_encoder));
}
