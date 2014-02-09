#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    MainWindow();

  public slots:
    void togglePower();
    void increaseBacklight();
    void decreaseBacklight();
    void sliderChanged(int new);

  private:
    Ui::MainWindow ui;
};

#endif
