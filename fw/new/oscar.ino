#include <Arduino.h>
#include <AdapterBoard.h>

AdapterBoard board;

void setup()
{
  board.init();
}

void loop()
{
  board.poll();
}

# vim:ft=c
