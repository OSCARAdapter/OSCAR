#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include"devicethread.h"

class MainWindow : public QWidget
{
  Q_OBJECT

  public:
    MainWindow();

    void togglePower();
    void increaseBacklight();
    void decreaseBacklight();
    void sliderChanged(int value);

    void backlightResponse(bool on, int level);
    void deviceConnected();
    void deviceNotConnected();

  private:
    void stylize();

    Ui::MainWindow ui;
    DeviceThread *dev;
};

#endif
