#include <main.h>
#include <Arduino.h>
#include "HID-Project.h"

void pressKey(int n) {
  Keyboard.press(keyCodes[n]);
  keys[n].pressed = true;
}

void releaseKey(int n) {
  Keyboard.release(keyCodes[n]);
  keys[n].pressed = false;
}

void convertDistance(int n) {
  keys[n].trigger = ((keys[n].max - keys[n].min) / BOTTOM_OUT_DISTANCE) * TRIGGER;
  keys[n].release = ((keys[n].max - keys[n].min) / BOTTOM_OUT_DISTANCE) * RELEASE;
}

void initKey(int n) {
  pinMode(keyPins[n],INPUT);
  keys[n].value = analogRead(keyPins[n]);
  keys[n].reference = keys[n].value;

  /* Idea is the more you use the key the more accurate the values are */
  keys[n].min = keys[n].value - CUSHION;
  keys[n].max = keys[n].value + CUSHION;

  /* These values are meaningless, it'll be replaced when min/max changes */
  keys[n].trigger = TRIGGER * CUSHION;
  keys[n].release = RELEASE * CUSHION;
}

void balanceKey(int n) {
  /* Min (rest) value will only be updated when key is not being pressed */
  if (!keys[n].pressed && (keys[n].value < keys[n].min)) {
    keys[n].min = keys[n].value;
    convertDistance(n);
  } else if (keys[n].pressed && (keys[n].value > keys[n].max)) {
    /* Same with max value */
    keys[n].max = keys[n].value;
    convertDistance(n);
  }
}

void processKey(int n) {
  /* Optimization: check if key is triggered first */
  if (!keys[n].pressed) {
    if (keys[n].value > keys[n].reference + keys[n].trigger) {
      pressKey(n);
    }

    if (keys[n].value < keys[n].reference) {
      keys[n].reference = keys[n].value;
    }
  } else if (keys[n].pressed) {
    if (keys[n].value <= keys[n].reference - keys[n].release) {
      releaseKey(n);
    }

    if (keys[n].value > keys[n].reference) {
      keys[n].reference = keys[n].value;
    }
  }
}

void runKey(int n) {
  keys[n].value = analogRead(keyPins[n]);
  balanceKey(n);
  processKey(n);
}

void setup() {
  for (int i = 0; i < KEYS; i++) {
    initKey(i);
  }
  Keyboard.begin();
}

void loop() {
  runKey(0);
  runKey(1);
}
