#include <RGBLed.h>
#include <Backlight.h>
#include <AdapterBoard.h>

AdapterBoard::AdapterBoard()
{
}

void AdapterBoard::init()
{
  //Initialize the led, set to 'standby'
  led.init(LED_R, LED_G, LED_B);
  led.set(1, 0, 0);

  //Setup backlight, restore previous brightness, but don't enable
  backlight.init(BACKLIGHT_PIN, SUPPLY_EN);
  backlight.setLast();
}

void AdapterBoard::poll()
{
}
