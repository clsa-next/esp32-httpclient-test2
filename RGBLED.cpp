#include "RGBLED.h"

RGBLED::RGBLED(int redPin, int greenPin, int bluePin)
: redPin(redPin), greenPin(greenPin), bluePin(bluePin) {}

void RGBLED::begin() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void RGBLED::setColor(int red, int green, int blue) {
  analogWrite(redPin, 255 - red);   // Common anode, invert values
  analogWrite(greenPin, 255 - green);
  analogWrite(bluePin, 255 - blue);
}
