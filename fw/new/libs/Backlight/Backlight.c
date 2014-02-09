#include <Arduino.h>
#include <EEPROM.h>
#include <Backlight.h>

void Backlight::init(int pin)
{
  pinMode(pin, OUTPUT);
  this.pin = pin;
}

void Backlight::set(int level)
{
  analogWrite(pin, level);
  EEPROM.write(0, level);
}

int Backlight::get()
{
  return EEPROM.read(0);
}

void Backlight::up()
{

}

void Backlight::down()
{

}
