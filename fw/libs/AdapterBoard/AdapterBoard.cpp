#include <RGBLed.h>
#include <Backlight.h>
#include <AdapterBoard.h>
#include <Arduino.h>
#include "usb_commands.h"

bool isUsb = false;
unsigned long lastPowerChange = 0;

AdapterBoard::AdapterBoard()
{
}

void AdapterBoard::init()
{
  //Initialize the led, set to 'standby'
  led.init(LED_R, LED_G, LED_B);
  led.set(STANDBY_COLOUR);

  //Initialize the switches on board
  initSwitches();
  delay(100);

  //Setup backlight, restore previous brightness, only enable if we were powered
  backlight.init(BACKLIGHT_PIN, SUPPLY_EN);
  backlight.setLast();
  backlight.setLastPowerState();
  if(backlight.isOn())
    led.set(ON_COLOUR);
}

void AdapterBoard::poll()
{
  //Check the switches, execute action if necessary
  pollSwitches();

  //Handle any USB commands waiting
  handleUSB();
}

void AdapterBoard::initSwitches()
{
  pinMode(SW_ON, INPUT);
  pinMode(SW_UP, INPUT);
  pinMode(SW_DOWN, INPUT);

  swOn = Bounce();
  swOn.attach(SW_ON);
  swOn.interval(SWITCH_DELAY);
  swUp = Bounce();
  swUp.attach(SW_UP);
  swUp.interval(SWITCH_DELAY);
  swDown = Bounce();
  swDown.attach(SW_DOWN);
  swDown.interval(SWITCH_DELAY);
}

void AdapterBoard::pollSwitches()
{
  if(swOn.update() && swOn.read() == LOW)
    togglePower();

  //When both pressed, backlight up button has priority
  if(swUp.update() && swUp.read() == LOW)
    backlight.up();
  if(swDown.update() && swDown.read() == LOW)
    backlight.down();
}

void AdapterBoard::togglePower()
{
  if((millis() - lastPowerChange) < 300)
    return;
  lastPowerChange = millis();

  if(backlight.isOn())
  {
    led.set(STANDBY_COLOUR);
    backlight.set(backlight.get());
    backlight.off();
  }
  else
  {
    if(isUsb)
      led.set(ONUSB_COLOUR);
    else
      led.set(ON_COLOUR);

    backlight.setLast();
    backlight.on();
  }
}

char buf[EP_LEN];

void AdapterBoard::handleUSB()
{
  if(usb.isEnumerated())
  {
    isUsb = true;
    if(backlight.isOn())
      led.set(ONUSB_COLOUR);

    if(usb.hasData())
    {
      char resp[EP_LEN];
      bool unknown = false;
      bool needsAck = true;
      usb.read(buf, EP_LEN);

      //Command type specifier stored in byte 0
      switch(buf[0])
      {
        case CMD_BL_ON:
          led.set(ONUSB_COLOUR);
          backlight.on();
          break;
        case CMD_BL_OFF:
          led.set(STANDBY_COLOUR);
          backlight.off();
          break;
        case CMD_BL_LEVEL:
          backlight.set(buf[1]);
          break;
        case CMD_BL_UP:
          backlight.up();
          break;
        case CMD_BL_DOWN:
          backlight.down();
          break;
        case CMD_BL_GET_STATE:
          needsAck = false;
          //Send state response
          resp[0] = CMD_RESP;
          resp[1] = CMD_BL_GET_STATE;
          resp[2] = backlight.isOn();
          resp[3] = backlight.get();
          while(!usb.canSend());
          usb.write(resp, EP_LEN);
          break;

        case CMD_RGB_SET:
          led.set(buf[1], buf[2], buf[3]);
          break;
        case CMD_RGB_GET:
          needsAck = false;
          //Send response
          resp[0] = CMD_RESP;
          resp[1] = CMD_RGB_GET;
          resp[2] = led.r;
          resp[2] = led.g;
          resp[3] = led.b;
          while(!usb.canSend());
          usb.write(resp, EP_LEN);
          break;

        default:
          unknown = true;
          break;
      }

      if(!unknown && needsAck)
      {
        //Send ACK back to PC
        resp[0] = CMD_ACK;
        resp[1] = buf[0];
        while(!usb.canSend());
        usb.write(resp, EP_LEN);
      }
    }
  }
  else
  {
    isUsb = false;
    if(backlight.isOn())
      led.set(ON_COLOUR);
  }
}
