#ifndef BACKLIGHT_H
#define BACKLIGHT_H

class Backlight
{
  public:
    void init(int pin);
    void set(int level);
    int get();

    void up();
    void down();

  private:
    int pin;
    int levels[] = {0, 1, 2, 3, 4, 6, 8, 12, 16, 23,
                    32, 45, 64, 90, 128, 180, 255};
};

#endif
