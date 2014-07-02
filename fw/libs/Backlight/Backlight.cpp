#include <EEPROM.h>
#include <Backlight.h>
#include <Arduino.h>

//Levels chosen by careful observation
#define NUM_LEVELS 17
int levels[] = {0, 1, 2, 3, 4, 6, 8, 12, 16, 23,
                      32, 45, 64, 90, 128, 180, 255};

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

void Backlight::set(uint8_t level)
{
  analogWrite(pwm_pin, level);
  current = level;
  EEPROM.write(eeprom, level);
}

void Backlight::setLast()
{
  set(EEPROM.read(eeprom));
}

uint8_t Backlight::get()
{
  return current;
}

void Backlight::up()
{
  int curStep = findNearestStep(get());
  if((curStep+1) < NUM_LEVELS)
    set(levels[curStep+1]);
}

void Backlight::down()
{
  int curStep = findNearestStep(get());
  if((curStep-1) >= 0)
    set(levels[curStep-1]);
}

int Backlight::findNearestStep(uint8_t level)
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
  int bl = get();
  analogWrite(pwm_pin, 0);
  digitalWrite(en_pin, 1);
  delay(300);
  analogWrite(pwm_pin, bl);
}

void Backlight::off()
{
  onState = false;
  analogWrite(pwm_pin, 0);
  delay(60);
  digitalWrite(en_pin, 0);
}

bool Backlight::isOn()
{
  return onState;
}
