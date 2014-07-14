#ifndef ADAPTERBOARD_H
#define ADAPTERBOARD_H

#include <Backlight.h>
#include <RGBLed.h>
#include <Bounce2.h>
#include <usb.h>

#define LED_R 9
#define LED_G 13
#define LED_B 10
#define BACKLIGHT_PIN 11
#define SUPPLY_EN 8

//When reading the switches, the logical value is inverted from the actual
//due to the board design.
#define SW_ON   4  //PD4
#define SW_UP   12 //PD6
#define SW_DOWN 6  //PD7

#define STANDBY_COLOUR 1, 0, 0
#define ON_COLOUR      0, 12, 0
#define ONUSB_COLOUR   12, 12, 12
#define SWITCH_DELAY   50

class AdapterBoard
{
  public:
    AdapterBoard();
    void init();
    void poll();

  private:
    void initSwitches();
    void pollSwitches();
    void handleUSB();

    void togglePower();

    RGBLed led;
    Backlight backlight;
    USB usb;

    Bounce swOn, swUp, swDown;
};

#endif
