# Handmade 2K Pro Micro ~~49E~~ 44E Linear Hall Effect Keypad

![project](https://raw.githubusercontent.com/chent7/hall-keypad/master/img/project.JPG)

Announcement: \
Please use the 44E instead of 49E for reasons explained in the pinned YouTube comment :) \
Use a compass to determine the south pole of the magnet (so the red needle points to the magnet \
And have it face the sensor

Build:
https://www.youtube.com/watch?v=EjJIpGJ4OQg

Updates:
* Build and Flash with PlatformIO
* Uses ![HID-Project library](https://registry.platformio.org/libraries/nicohood/HID-Project)
* Keys now self-balance (give it a few taps for trigger to be accurate)
* Some code optimizations:
```
Evading for loops, no declaration, assignment and incrementation. Should also be viable on a full size keyboard (but not sure if copy and pasting 60-70 lines is a good way)

Minimizing checks, outer most if statements should be limited to as little checks as possible
```
* Still some room for improvments to come
