#include <EEPROM.h>
#include <Backlight.h>
#include <Arduino.h>

void Backlight::init(int pin_pwm, int pin_en, int eeprom_location)
{
  pwm_pin = pin_pwm;
  en_pin = pin_en;
  eeprom = eeprom_location;
  current = levels[0];
  onState = false;

  pinMode(pwm_pin, OUTPUT);
  pinMode(en_pin, OUTPUT);
  off();
}

void Backlight::set(int level)
{
  analogWrite(pwm_pin, level);
  current = level;
  EEPROM.write(eeprom, level);
}

void Backlight::setLast()
{
  set(EEPROM.read(eeprom));
}

int Backlight::get()
{
  return current;
}

void Backlight::up()
{
  int curStep = findNearestStep(get());
  int nextStep = curStep++;
  if(nextStep < NUM_LEVELS)
    set(levels[nextStep]);
}

void Backlight::down()
{
  int curStep = findNearestStep(get());
  int nextStep = curStep--;
  if(nextStep >= 0)
    set(levels[nextStep]);
}

int Backlight::findNearestStep(int level)
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

void Backlight::on()
{
  onState = true;
  digitalWrite(en_pin, 1);
}

void Backlight::off()
{
  onState = false;
  digitalWrite(en_pin, 0);
}

bool Backlight::isOn()
{
  return onState;
}
