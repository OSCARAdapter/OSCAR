#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    MainWindow();

  private:
    Ui::MainWindow ui;
};

#endif
