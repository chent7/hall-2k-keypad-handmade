#include <Arduino.h>
#include "HID-Project.h"

/* Key Parameters */
struct keyData {
  int min;
  int max;
  int trigger;
  int release;
  int value;
  int reference;
  bool pressed;
};

#define KEYS 2 // number of keys and leds
#define CUSHION 10

/* Switch parameters in mm */
#define TRIGGER 0.9
#define RELEASE 0.8
#define BOTTOM_OUT_DISTANCE 4

keyData keys[KEYS];
const static uint8_t keyPins[KEYS] = { A1, A0 };
KeyboardKeycode keyCodes[KEYS] = {KEY_Z, KEY_X};
