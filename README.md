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

## Lightbox and stencils
The lightbox reflects light out from the box along a parabolic curve that gives the effect of 8 straightish beams of light that appear to be extending behind the light box indefinitely. The lightbox can also be run without any stencil, giving full view of the light beams (this is what 'neon vectors' alludes to).

A stencil with holes to reveal the light can be slotted into the front of the light box, and it is interchangable for any stencil that fits. The dimensions for the stencil are 100mm wide by 140mm high and 1.5mm thick. The original stencil has a 1mm chamfer to help with sliding the stencil in but this is not essential because the slot is oversized (~3mm but probably slightly smaller after 3d printing due to tolerances). While the original stencil is 3d printed, other materials such as card can be used. A black stencil is most effective to contrast with the light shining from inside the lightbox, but any colour will work.

Have fun!
