# Handmade 2K Pro Micro ~~49E~~ 44E Linear Hall Effect Keypad

![project](https://raw.githubusercontent.com/chent7/hall-keypad/master/img/project.JPG)

## Announcement:
Please use the 44E instead of 49E for reasons explained in the pinned YouTube comment :) \
Use a compass to determine the south pole of the magnet (so the red needle points to the magnet) \
And have it face the sensor

## Build:
https://www.youtube.com/watch?v=EjJIpGJ4OQg

## Updates:
* Build and Flash with PlatformIO
* Uses ![HID-Project library](https://registry.platformio.org/libraries/nicohood/HID-Project)
* Keys now self-balance (give it a few taps for trigger to be accurate)
* Some optimizations:
   * Custom USB device name, vid/pid
   * Evading loops
   * Minimizing checks
   * NKRO (WIP)
   * Save/Load EEPROM (WIP)
   * Online Configurator (WIP)
   * Threading workload (WIP)
