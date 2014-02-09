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

  prev_swOn = HIGH;
  prev_swUp = HIGH;
  prev_swDown = HIGH;
  switchDelay = 0;
}

void AdapterBoard::pollSwitches()
{
  //Ignore a few polls
  if(switchDelay++ < 1000)
    return;

  int swOn = digitalRead(SW_ON);
  int swUp = digitalRead(SW_UP);
  int swDown = digitalRead(SW_DOWN);

  if(swOn == LOW && prev_swOn == HIGH)
    togglePower();

  //When both pressed, backlight up button has priority
  if(swUp == LOW && prev_swUp == HIGH)
    backlight.up();
  else if(swDown == LOW && prev_swDown == HIGH)
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
