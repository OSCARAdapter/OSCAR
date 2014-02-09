#include <RGBLed.h>
#include <Backlight.h>
#include <AdapterBoard.h>
#include <Arduino.h>

AdapterBoard::AdapterBoard()
{
}

void AdapterBoard::init()
{
  //Initialize the led, set to 'standby'
  led.init(LED_R, LED_G, LED_B);
  led.set(STANDBY_COLOUR);

  //Setup backlight, restore previous brightness, but don't enable
  backlight.init(BACKLIGHT_PIN, SUPPLY_EN);
  backlight.setLast();

  //Initialize the switches on board
  initSwitches();
}

void AdapterBoard::poll()
{
  //Check the switches, execute action if necessary
  pollSwitches();

  //TODO: USB?
}

void AdapterBoard::initSwitches()
{
  pinMode(SW_ON, INPUT);
  pinMode(SW_UP, INPUT);
  pinMode(SW_DOWN, INPUT);

  prev_swOn = !digitalRead(SW_ON);
  prev_swUp = !digitalRead(SW_UP);
  prev_swDown = !digitalRead(SW_DOWN);
}

void AdapterBoard::pollSwitches()
{
  boolean swOn = !digitalRead(SW_ON);
  boolean swUp = !digitalRead(SW_UP);
  boolean swDown = !digitalRead(SW_DOWN);

  if(swOn == HIGH && prev_swOn == LOW)
    togglePower();

  //When both pressed, backlight up button has priority
  if(swUp == HIGH && prev_swUp == LOW)
    backlight.up();
  else if(swDown == HIGH && prev_swDown == LOW)
    backlight.down();

  prev_swOn = swOn;
  prev_swUp = swUp;
  prev_swDown = swDown;
}

void AdapterBoard::togglePower()
{
  if(backlight.isOn())
  {
    backlight.off();
    led.set(STANDBY_COLOUR);
  }
  else
  {
    backlight.setLast();
    backlight.on();
    led.set(ON_COLOUR);
  }
}
