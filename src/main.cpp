#include <Arduino.h>
#include "HID-Project.h"

struct keyData {
  int min;
  int max;
  int trig;
  int val;
  int ref;
  bool pressed;
};

#define CUSHION 10

#define KEYS_NUM 2
#define RAPID_TRIGGER_DISTANCE 0.9 // in mm
#define BOTTOM_OUT_DISTANCE 4 // in mm

keyData keys[KEYS_NUM];
const static uint8_t keyPins[KEYS_NUM] = { A1, A0 };
const static char keyChars[KEYS_NUM] = { 'z', 'x' };

void pressKey(int n) {
  Keyboard.press(keyChars[n]);
  keys[n].pressed = true;
}

void releaseKey(int n) {
  Keyboard.release(keyChars[n]);
  keys[n].pressed = false;
}

void initKey(int n) {
  pinMode(keyPins[n],INPUT);
  keys[n].val = analogRead(keyPins[n]);
  keys[n].ref = keys[n].val;
  keys[n].min = keys[n].val - CUSHION;
  keys[n].max = keys[n].val + CUSHION;
  keys[n].trig = RAPID_TRIGGER_DISTANCE * CUSHION;
}

void balanceKey(int n) {
  if (keys[n].val < keys[n].min) {
    keys[n].min = keys[n].val;
    keys[n].trig = ((keys[n].max - keys[n].min) / BOTTOM_OUT_DISTANCE) * RAPID_TRIGGER_DISTANCE;
  } else if (keys[n].val > keys[n].max) {
    keys[n].max = keys[n].val;
    keys[n].trig = ((keys[n].max - keys[n].min) / BOTTOM_OUT_DISTANCE) * RAPID_TRIGGER_DISTANCE;
  }
}

void processKey(int n) {
  if (keys[n].val > keys[n].ref + keys[n].trig && !keys[n].pressed) {
    pressKey(n);
  } else if (keys[n].val <= keys[n].ref - keys[n].trig && keys[n].pressed) {
    releaseKey(n);
  }

  if ((keys[n].pressed && keys[n].val > keys[n].ref) || \
      (!keys[n].pressed && keys[n].val < keys[n].ref)) {
    keys[n].ref = keys[n].val;
  }
}

void runKey(int n) {
  keys[n].val = analogRead(keyPins[n]);
  balanceKey(n);
  processKey(n);
}

void setup() {
  initKey(0);
  initKey(1);
  Keyboard.begin();
}

void loop() {
  runKey(0);
  runKey(1);
}