#include <QtGui>
#ifdef Q_OS_WIN
#include <QtWinExtras>
#endif
#include "mainwindow.h"
#include "usb_commands.h"

MainWindow::MainWindow()
{
  ui.setupUi(this);
  stylize();
  deviceNotConnected();

  dev = new DeviceThread();
  dev->start();

  connect(ui.powerButton, SIGNAL(clicked()), this, SLOT(togglePower()));
  connect(ui.upButton, SIGNAL(clicked()), this, SLOT(increaseBacklight()));
  connect(ui.downButton, SIGNAL(clicked()), this, SLOT(decreaseBacklight()));
  connect(ui.backlightSlider, SIGNAL(valueChanged(int)), this, SLOT(sliderChanged(int)));

  connect(dev, SIGNAL(backlightResponse(bool, int)), this, SLOT(backlightResponse(bool, int)));
  connect(dev, SIGNAL(connected()), this, SLOT(deviceConnected()));
  connect(dev, SIGNAL(notConnected()), this, SLOT(deviceNotConnected()));
}

MainWindow::~MainWindow()
{
  dev->finish();
}

void MainWindow::stylize()
{
#ifdef Q_OS_WIN
  if(QtWin::isCompositionEnabled())
  {
    QtWin::enableBlurBehindWindow(this);
    QtWin::extendFrameIntoClientArea(this, -1, -1, -1, -1);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_NoSystemBackground, true);
  }
#endif
}

void MainWindow::togglePower()
{
  if(ui.powerButton->text() == "On")
  {
    ui.powerButton->setText("Off");
    dev->setBacklightPower(true);
  }
  else
  {
    ui.powerButton->setText("On");
    dev->setBacklightPower(false);
  }
}

void MainWindow::increaseBacklight()
{
  Command_t cmd;
  cmd.cmd = CMD_BL_UP;
  dev->enqueue(cmd);
}

void MainWindow::decreaseBacklight()
{
  Command_t cmd;
  cmd.cmd = CMD_BL_DOWN;
  dev->enqueue(cmd);
}

void MainWindow::sliderChanged(int value)
{
  dev->setBacklightLevel(value);
}

void MainWindow::backlightResponse(bool on, int level)
{
  ui.backlightSlider->setValue(level);
  if(on)
    ui.powerButton->setText("Off");
  else
    ui.powerButton->setText("On");
}

void MainWindow::deviceConnected()
{
  ui.statusLabel->setVisible(false);
  ui.powerButton->setEnabled(true);
  ui.upButton->setVisible(true);
  ui.downButton->setVisible(true);
  ui.backlightSlider->setVisible(true);
  ui.backlightLabel->setVisible(true);
}

void MainWindow::deviceNotConnected()
{
  ui.statusLabel->setVisible(true);
  ui.statusLabel->setText("Unable to connect to OSCAR");
  ui.powerButton->setEnabled(false);
  ui.upButton->setVisible(false);
  ui.downButton->setVisible(false);
  ui.backlightSlider->setVisible(false);
  ui.backlightLabel->setVisible(false);
}
