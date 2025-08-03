//code for ATTINY85 neonvectors light box by BeansMachines
//with signficant code for rainbow mode borrowed from https://github.com/smartynov/iotfun/blob/master/arduino/deco_lights/deco_lights.ino


//USE JUST ONE SET OF LIBRARY INCLUDES DEPENDING ON YOUR IDE

//Arduino IDE
#include <Adafruit_NeoPixel.h> //Adafruit Neopixel by Adafruit version 1.11.0 installed (in Arduino IDE, just have the .h file name without the folder)
#include <EEPROM.h> //arduino native probably

/*
//NOT YET WORKING: testing vscode with arduino maker workshop
//#include <./Adafruit_NeoPixel/Adafruit_NeoPixel.h> //Adafruit Neopixel by Adafruit version 1.11.0 installed (in Arduino IDE, just have the .h file name without the folder)
#include <C:\Users\chris\AppData\Local\Arduino15\packages\ATTinyCore\hardware\avr\1.5.2\libraries\EEPROM\EEPROM.h> //arduino native probably
#include <C:\Users\chris\AppData\Local\Arduino15\packages\arduino\tools\avr-gcc\7.3.0-atmel3.6.1-arduino7\avr\include\inttypes.h> //required for vscode
#include <C:\Users\chris\AppData\Local\Arduino15\packages\arduino\tools\avr-gcc\7.3.0-atmel3.6.1-arduino7\avr\include\stdint.h> //required for vscode
//#include <C:\Users\chris\AppData\Local\Arduino15\packages\arduino\tools\avr-gcc\7.3.0-atmel3.6.1-arduino7\lib\gcc\avr\7.3.0\include\stdint.h>
*/

// set to pin connected to data input of WS8212 (NeoPixel) strip
#define PIN         2

// any pin with analog input (used to initialize random number generator)
#define RNDPIN      3

// number of LEDs (NeoPixels) in your strip
// (please note that you need 3 bytes of RAM available for each pixel)
#define NUMPIXELS   8
// max LED brightness (1 to 255) – start with low values!
// (please note that high brightness requires a LOT of power)
#define BRIGHTNESS  255

// increase to get narrow spots, decrease to get wider spots
#define FOCUS       65

// decrease to speed up, increase to slow down (it's not a delay actually)
#define DELAY       2000

// set to 1 to display FPS rate
//#define DEBUG       0

// if true, wrap color wave over the edge (used for circular stripes)
#define WRAP        1


Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// we have 3 color spots (reg, green, blue) oscillating along the strip with different speeds
float spdr, spdg, spdb;
float offset;

// #if DEBUG
// // track fps rate
// long nextms = 0;
// int pfps = 0, fps = 0;
// #endif

// the real exponent function is too slow, so I created an approximation (only for x < 0)
float myexp(float x) {
  return (1.0/(1.0-(0.634-1.344*x)*x));
}


//eeprom
int eepromaddress = 0;
int eepromreadvalue1;
int eepromreadvalue2;
uint8_t eepromwritevalue;
bool neonmode = false;
bool fireglowmode = false;

void setup() {

  //recall last used mode and set current mode
  eepromroutine();
  
  // initialize pseudo-random number generator with some random value
  randomSeed(analogRead(RNDPIN));

  // assign random speed to each spot
  spdr = 1.0 + random(200) / 100.0;
  spdg = 1.0 + random(200) / 100.0;
  spdb = 1.0 + random(200) / 100.0;

  // set random offset so spots start in random locations
  offset = random(10000) / 100.0;

  // initialize LED strip
  strip.begin();
  strip.show();

  if(neonmode == true){
    //neonmode
    neonmodeloop();
  }

  if(fireglowmode == true){
      //fire glow mode
      firegloweffect();
  }

}

//main loop is for rainbow mode only
void loop() {

  // use real time to recalculate position of each color spot
  long ms = millis();
  // scale time to float value
  float m = offset + (float)ms/DELAY;
  // add some non-linearity
  m = m - 42.5*cos(m/552.0) - 6.5*cos(m/142.0);

  // recalculate position of each spot (measured on a scale of 0 to 1)
  float posr = 0.15 + 0.55*sin(m*spdr);
  float posg = 0.5 + 0.65*sin(m*spdg);
  float posb = 0.85 + 0.75*sin(m*spdb);

  // now iterate over each pixel and calculate it's color
  for (int i=0; i<NUMPIXELS; i++) {
    // pixel position on a scale from 0.0 to 1.0
    float ppos = (float)i / NUMPIXELS;
 
    // distance from this pixel to the center of each color spot
    float dr = ppos-posr;
    float dg = ppos-posg;
    float db = ppos-posb;
#if WRAP
    dr = dr - floor(dr + 0.5);
    dg = dg - floor(dg + 0.5);
    db = db - floor(db + 0.5);
#endif

    // set each color component from 0 to max BRIGHTNESS, according to Gaussian distribution
    strip.setPixelColor(i,
      constrain(BRIGHTNESS*myexp(-FOCUS*dr*dr),0,BRIGHTNESS),
      constrain(BRIGHTNESS*myexp(-FOCUS*dg*dg),0,BRIGHTNESS),
      constrain(BRIGHTNESS*myexp(-FOCUS*db*db),0,BRIGHTNESS)
      );
  }

// #if DEBUG
//   // keep track of FPS rate
//   fps++;
//   if (ms>nextms) {
//     // 1 second passed – reset counter
//     nextms = ms + 1000;
//     pfps = fps;
//     fps = 0;
//   }
//   // show FPS rate by setting one pixel to white
//   strip.setPixelColor(pfps,BRIGHTNESS,BRIGHTNESS,BRIGHTNESS);
// #endif

  // send data to LED strip
  strip.show();
}


void eepromroutine(){
  EEPROM.get(eepromaddress, eepromreadvalue1);

  //for power on or having issues
  if(eepromreadvalue1 == 0 || eepromreadvalue1 == 1 || eepromreadvalue1 == 2){
    //only force zero if is not one of the desired values
  } else {EEPROM.put(eepromaddress, 0);}
  
  if(eepromreadvalue1 == 0){
    neonmode = false;
    fireglowmode = false;
    eepromwritevalue = eepromreadvalue1 + 1;
    EEPROM.put(eepromaddress, eepromwritevalue);
  } else if(eepromreadvalue1 == 1){
    neonmode = true;
    fireglowmode = false;
    eepromwritevalue = eepromreadvalue1 + 1;
    EEPROM.put(eepromaddress, eepromwritevalue);
  } else if(eepromreadvalue1 == 2){
    neonmode = false;
    fireglowmode = true;
    eepromwritevalue = eepromreadvalue1 - 2;
    EEPROM.put(eepromaddress, eepromwritevalue);
  }

  EEPROM.get(eepromaddress, eepromreadvalue2);
}

void neonmodeloop(){
  while(1==1){
    for(int i=0; i<8; i++){
      strip.setPixelColor(i,255,40,150);
    }
    strip.show();
    delay(5000);
  }
}

void firegloweffect(){
  //effect vars
  int red = 255;
  int green = 60;
  int redglow;
  int greenglow;

    while(1==1){
      
      for(int i=0; i<NUMPIXELS; i++) {
        int flicker = random(0,64);
        redglow = red - flicker;
        greenglow = green - flicker;
        if(redglow<0){redglow = 0;}
        if(greenglow<0){greenglow = 0;}
        strip.setPixelColor(i, strip.Color(redglow, greenglow, 0));
      }
      strip.show();
    
      delay(random(20,255));
    }
  //}
}