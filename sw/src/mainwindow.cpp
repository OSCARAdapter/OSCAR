#include <QtGui>
#include "mainwindow.h"

MainWindow::MainWindow()
{
  ui.setupUi(this);

  CONNECT(powerButton, clicked(), this, togglePower());
  CONNECT(upButton, clicked(), this, increaseBacklight());
  CONNECT(downButton, clicked(), this, decreaseBacklight());
  CONNECT(backlightSlider, valueChanged(int), this, sliderChanged(int));
}

void MainWindow::togglePower()
{
  //TODO: implement sending via USB
  if(powerButton.text == "On")
  {
    powerButton.text = "Off";
  }
  else
  {
    powerButton.text = "On";
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

void bodgeIncrease()
{
  int curStep = bodgeFindNearestStep(backlightSlider.value);
  if((curStep+1) < NUM_LEVELS)
    backlightSlider.value = levels[curStep+1];
}

void bodgeDecrease()
{
  int curStep = bodgeFindNearestStep(backlightSlider.value);
  if((curStep-1) >= 0)
    backlightSlider.value = levels[curStep-1];
}
/*-----------------BODGE END------------------------------ */

void MainWindow::increaseBacklight()
{
  //TODO: send
  bodgeIncrease();
}

void MainWindow::decreaseBacklight()
{
  //TODO: send
  bodgeDecrease();
}
