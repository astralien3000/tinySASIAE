#include "mainwindow.hpp"
#include <QApplication>
#include <QCommandLineParser>
#include <QTimer>

#include <iostream>

#include <cmath>
#include "physicsengine.hpp"
#include "robotbin.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("tinySASIAE");
    app.setApplicationVersion("18.06");

    QCommandLineParser parser;
    parser.setApplicationDescription("Simple robot simulator");
    const QCommandLineOption help_option = parser.addHelpOption();
    const QCommandLineOption version_option = parser.addVersionOption();

    const QCommandLineOption robotbin_option("r", "Robot binary", "path");
    parser.addOption(robotbin_option);

    parser.process(app);

    if(parser.isSet(version_option)) {
      std::cout << qPrintable(app.applicationName()) << " " << qPrintable(app.applicationVersion()) << std::endl;
      return 0;
    }

    if(parser.isSet(help_option)) {
      std::cout << qPrintable(parser.helpText()) << std::endl;
      return 0;
    }

    if(parser.isSet(robotbin_option)) {
      QStringList list = parser.values(robotbin_option);
      for(QStringList::Iterator it = list.begin() ; it != list.end() ; it++) {
        std::cout << qPrintable(*it) << std::endl;
      }
    }

    Robot r;
    r.width = 50;

    PhysicsEngine engine(r);

    QTimer timer;
    timer.setInterval(1000.0 / 60.0);

    MainWindow w(r);
    w.show();
    w.showMaximized();
    w.update();

    //RobotBin bin(r, engine);

    //timer.connect(&timer, SIGNAL(timeout()), &bin, SLOT(update()));
    timer.connect(&timer, SIGNAL(timeout()), &engine, SLOT(update()));
    timer.connect(&timer, SIGNAL(timeout()), &w, SLOT(update()));

    timer.start();

    return app.exec();
}
