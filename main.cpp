#include "mainwindow.hpp"
#include <QApplication>
#include <QCommandLineParser>
#include <QTimer>
#include <QDebug>

#include <iostream>

#include <cmath>
#include "physics.hpp"
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

    MainWindow mwin;
    mwin.show();

    if(parser.isSet(robotbin_option)) {
      QStringList list = parser.values(robotbin_option);
      for(QStringList::Iterator it = list.begin() ; it != list.end() ; it++) {
        mwin.addRobot(new RobotBin(*it));
      }
    }

    return app.exec();
}
