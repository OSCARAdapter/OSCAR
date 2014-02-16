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
  dev = new DeviceThread();
  dev->start();

  connect(ui.powerButton, SIGNAL(clicked()), this, SLOT(togglePower()));
  connect(ui.upButton, SIGNAL(clicked()), this, SLOT(increaseBacklight()));
  connect(ui.downButton, SIGNAL(clicked()), this, SLOT(decreaseBacklight()));
  connect(ui.backlightSlider, SIGNAL(sliderMoved(int)), this, SLOT(sliderChanged(int)));

  connect(dev, SIGNAL(backlightResponse(bool, int)), this, SLOT(backlightResponse(bool, int)));
  connect(dev, SIGNAL(connected()), this, SLOT(deviceConnected()));
  connect(dev, SIGNAL(notConnected()), this, SLOT(deviceNotConnected()));
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
  //TODO: implement sending via USB
  if(ui.powerButton->text() == "On")
  {
    ui.powerButton->setText("Off");
  }
  else
  {
    ui.powerButton->setText("On");
  }
}

/*-----------------BODGE BEGIN---------------------------- */
#define NUM_LEVELS 17
const int levels[] = {0, 1, 2, 3, 4, 6, 8, 12, 16, 23,
                      32, 45, 64, 90, 128, 180, 255};
int bodgeFindNearestStep(int level)
{
  if(level > levels[NUM_LEVELS-2])
    return NUM_LEVELS-1;

  for(int i=0; i<NUM_LEVELS-1; i++)
  {
    if((levels[i] <= level) && (levels[i+1] > level))
      return i;
  }

  return 0;
}

void bodgeIncrease(Ui::MainWindow ui)
{
  int curStep = bodgeFindNearestStep(ui.backlightSlider->value());
  if((curStep+1) < NUM_LEVELS)
    ui.backlightSlider->setValue(levels[curStep+1]);
}

void bodgeDecrease(Ui::MainWindow ui)
{
  int curStep = bodgeFindNearestStep(ui.backlightSlider->value());
  if((curStep-1) >= 0)
    ui.backlightSlider->setValue(levels[curStep-1]);
}
/*-----------------BODGE END------------------------------ */

void MainWindow::increaseBacklight()
{
  bodgeIncrease(ui);
  Command_t cmd;
  cmd.cmd = CMD_BL_UP;
  dev->enqueue(cmd);
}

void MainWindow::decreaseBacklight()
{
  bodgeDecrease(ui);
  Command_t cmd;
  cmd.cmd = CMD_BL_DOWN;
  dev->enqueue(cmd);
}

void MainWindow::sliderChanged(int value)
{
  Command_t cmd;
  cmd.cmd = CMD_BL_LEVEL;
  cmd.arg1 = value;
  dev->enqueue(cmd);
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
  //ui.statusLabel.setText("Connected to OSCAR");
}

void MainWindow::deviceNotConnected()
{
  //ui.statusLabel.setText("Disconnected from OSCAR");
}
