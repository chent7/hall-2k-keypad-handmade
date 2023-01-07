#include "keyboard.h"

struct data {
  int val;
  int ref;
  bool pressed;
  float trig;
};

struct key {
  uint8_t pin;
  char key;
  float min;
  float max;
  data keyData;
};

#define RAPID_TRIGGER_DISTANCE 1.0 // in mm
#define NUM_OF_KEYS 2

key keys[NUM_OF_KEYS];

void setup() {
  data defaultData = {0, 0, false, 0};

  // Enter KEYS here
  keys[0] = {A1, 'KEY_Z', 528, 580, defaultData};
  keys[1] = {A0, 'KEY_X', 527, 578, defaultData};

  for (int i = 0; i < NUM_OF_KEYS; i++) {
    keys[i].keyData.trig = ((keys[i].max - keys[i].min) / 4) * RAPID_TRIGGER_DISTANCE; // only conversion done

    pinMode(keys[i].pin,INPUT);
    keys[i].keyData.val = analogRead(keys[i].pin);
    keys[i].keyData.ref = keys[i].keyData.val;
  }
  
  Keyboard.begin();
}

void loop() {

  for (int i = 0; i < NUM_OF_KEYS; i++) {
    keys[i].keyData.val = analogRead(keys[i].pin);

    if (keys[i].keyData.val > keys[i].keyData.ref + keys[i].keyData.trig && !keys[i].keyData.pressed) {
      pressKey(i);
    } else if (keys[i].keyData.val <= keys[i].keyData.ref - keys[i].keyData.trig && keys[i].keyData.pressed) {
      releaseKey(i);
    }

    if ((keys[i].keyData.pressed && keys[i].keyData.val > keys[i].keyData.ref) || \ 
        (!keys[i].keyData.pressed && keys[i].keyData.val < keys[i].keyData.ref)) {
      keys[i].keyData.ref = keys[i].keyData.val;
    }
  }

}

void pressKey(int keyNum) {
  Keyboard.press(keys[keyNum].key);
  keys[keyNum].keyData.pressed = true;
}

void releaseKey(int keyNum) {
  Keyboard.release(keys[keyNum].key);
  keys[keyNum].keyData.pressed = false;
}
