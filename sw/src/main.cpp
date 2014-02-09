#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  app.setOrganizationName("eeZySys Technologies");
  app.setApplicationName("OSCAR");
  MainWindow mainWin;
  mainWin.show();
  return app.exec();
}
