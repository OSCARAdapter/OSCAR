#include <compiler.h>

#ifndef BACKLIGHT_H
#define BACKLIGHT_H

class Backlight
{
  public:
    void init(int pwm_pin, int en_pin, int eeprom = 0);
    void set(uint8_t level);
    void setLast();
    uint8_t get();

    void up();
    void down();

    void on();
    void off();
    bool isOn();

  private:
    int findNearestStep(uint8_t level);

    int pwm_pin;
    int en_pin;
    int eeprom;
    uint8_t current;
    bool onState;
};

#endif
