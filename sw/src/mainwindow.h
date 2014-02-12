#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

class MainWindow : public QWidget
{
  Q_OBJECT

  public:
    MainWindow();

  public slots:
    void togglePower();
    void increaseBacklight();
    void decreaseBacklight();
    void sliderChanged(int value);

  private:
    void stylize();
    Ui::MainWindow ui;
};

#endif
