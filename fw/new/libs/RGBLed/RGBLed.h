#ifndef RGBLED_H
#define RGBLED_H

class RGBLed
{
  public:
    void init(int pinR, int pinG, int pinB);
    void set(int r, int g, int b);
};

#endif
