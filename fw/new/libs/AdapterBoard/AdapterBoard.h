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

  //Setup backlight, restore value
  backlight.init(BACKLIGHT_PIN);
  backlight.setLast();
}

void AdapterBoard::poll()
{
}
