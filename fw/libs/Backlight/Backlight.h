#ifndef BACKLIGHT_H
#define BACKLIGHT_H

class Backlight
{
  public:
    void init(int pwm_pin, int en_pin, int eeprom = 0);
    void set(int level);
    void setLast();
    int get();

    void up();
    void down();

    void on();
    void off();
    bool isOn();

  private:
    int findNearestStep(int level);

    int pwm_pin;
    int en_pin;
    int eeprom;
    int current;
    bool onState;
};

#endif
