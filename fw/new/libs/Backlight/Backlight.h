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

    //Levels chosen by careful observation
#define NUM_LEVELS 17
    int levels[] = {0, 1, 2, 3, 4, 6, 8, 12, 16, 23,
                    32, 45, 64, 90, 128, 180, 255};
};

#endif
