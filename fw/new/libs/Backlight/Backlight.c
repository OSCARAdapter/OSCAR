#include <Arduino.h>
#include <EEPROM.h>
#include <Backlight.h>

void Backlight::init(int pwm_pin, int en_pin, int eeprom)
{
  this.pwm_pin = pwm_pin;
  this.en_pin = en_pin;
  this.eeprom = eeprom;
  current = levels[0];

  pinMode(pwm_pin, OUTPUT);
  pinMode(en_pin, OUTPUT);
  off();
}

void Backlight::set(int level)
{
  analogWrite(pin, level);
  current = level;
  EEPROM.write(eeprom, level);
}

void Backlight::setLast()
{
  this.set(EEPROM.read(eeprom));
}

int Backlight::get()
{
  return current;
}

void Backlight::up()
{
  int nextStep = findNearestStep(this.get())++;
  if(nextStep < NUM_LEVELS)
    this.set(levels[nextStep]);
}

void Backlight::down()
{
  int nextStep = findNearestStep(this.get())--;
  if(nextStep >= 0)
    this.set(levels[nextStep]);
}

int Backlight::findNearestStep(int level)
{
  if(level > levels[NUM_LEVELS-2])
    return NUM_LEVELS-1;

  for(int i=0; i<NUM_LEVELS-1; i++)
  {
    if((levels[i] =< level) && (levels[i+1] > level))
      return i;
  }

  return 0;
}

void Backlight::on()
{
  digitalWrite(en_pin, 1);
}

void Backlight::off()
{
  digitalWrite(en_pin, 0);
}
