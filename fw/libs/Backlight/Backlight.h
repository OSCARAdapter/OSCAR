#include <compiler.h>

#ifndef BACKLIGHT_H
#define BACKLIGHT_H

/* Uses EEPROM locations as follows:
 * [eeprom] stores the last value of the backlight pwm
 * [eeprom+1] stores the last power state */

class Backlight
{
  public:
    void init(int pwm_pin, int en_pin, int eeprom = 0);
    void silentSet(uint8_t level);
    void set(uint8_t level);
    void setLast();
    void setLastPowerState();
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
