#include <RGBLed.h>

void RGBLed::init(int pinR, int pinB, int pinB)
{
  pinMode(pinR, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinB, OUTPUT);
  set(0, 0, 0);
}

void RGBLed::set(int r, int g, int b)
{
  analogWrite(pinR, r);
  analogWrite(pinG, g);
  analogWrite(pinB, b);
}
