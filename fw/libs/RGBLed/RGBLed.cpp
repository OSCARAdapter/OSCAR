#include <RGBLed.h>
#include <Arduino.h>

void RGBLed::init(int pinR, int pinG, int pinB)
{
  r_pin = pinR;
  g_pin = pinG;
  b_pin = pinB;

  pinMode(r_pin, OUTPUT);
  pinMode(g_pin, OUTPUT);
  pinMode(b_pin, OUTPUT);

  set(0, 0, 0);
}

void RGBLed::set(int xr, int xg, int xb)
{
  r = xr;
  g = xg;
  b = xb;
  analogWrite(r_pin, r);
  analogWrite(g_pin, g);
  analogWrite(b_pin, b);
}
