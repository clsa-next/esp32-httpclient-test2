#ifndef RGBLED_H
#define RGBLED_H

#include <Arduino.h>

class RGBLED {
public:
  RGBLED(int redPin, int greenPin, int bluePin);
  void begin();
  void setColor(int red, int green, int blue);

private:
  int redPin;
  int greenPin;
  int bluePin;
};

#endif // RGBLED_H
