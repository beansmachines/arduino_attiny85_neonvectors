# arduino_attiny85_neonvectors
Arduino code for attiny85 "neon vectors" lightbox gift

This code borrows heavily from https://github.com/smartynov/iotfun/blob/master/arduino/deco_lights/deco_lights.ino

It has an 8-LED neopixel strip driven by a small ATTINY85 digispark-clone board with USB connectivity broken out in a separate USB port for programming.

## Requirements
- A way to compile code for Arduino family (including the ATTINY85) and libraries (arduino-native EEPROM and adafruit neopixel library), such as with the native Arduino IDE. See note about IDE choice below.
- Arduino-compatible module. Only the ATTINY85 is tested but other modules are likely to work perhaps with some minor adjustments. Pin #2 is used on the ATTINY85 lightbox gift to drive the neopixels but most other pins should work too.

## Installation instructions
- clone the repo or otherwise save the .ino file and it's folder on your system
- run your IDE of choice with suitable libraries
- flash the arduino-compatible module

### VSCode compile issues
I was unable to get the code compile with VSCode and the Arduino Maker Workshop extension, though that could be down to a PEBKAC. Something something compiling C is not set up properly on my install perhaps. Arduino IDE works, which is available for Windows, Mac & Linux.

### Flashing the ATTINY85
For the ATTINY85, flashing it involves plugging in the USB cable *after* flashing has been intiated on the PC. This is because the ATTINY85 has a short delay of a few seconds upon power on for it to enter flashing mode, and flashing cannot begin after this delay has passed. It also explains why it takes about 5sec after power on to show anything on the neopixels.


