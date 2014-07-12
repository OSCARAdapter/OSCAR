#include <RGBLed.h>
#include <Backlight.h>
#include <AdapterBoard.h>
#include <Arduino.h>
#include "usb_commands.h"

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

  //Handle any USB commands waiting
  handleUSB();
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
  if(swDown == LOW && prev_swDown == HIGH)
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
          backlight.on();
          break;
        case CMD_BL_OFF:
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
}
