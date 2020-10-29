#include <FastLED.h> // LED Strip library (and so much more)...honestly one of my favorite Arduino libraries

void setup() {
  led_setup();
}

uint8_t count = 0;
void loop() {
  set_left_led_color_hsv(CHSV(count, 255, 255)); // If you don't know what HSV colors are...look them up now! Imagine trying to code up
  set_right_led_color_hsv(CHSV(255 - count, 255, 255)); // a rainbow pattern in the rgb space...I'm shivering thinking about it! With HSV,
                                                        // we just increment the hue value and the colors will automatically cycle correctly
  update_leds();

  count++; // What's nice about making count a uint8_t is that we don't have to add logic
           // to wrap around the variable. count will naturally wrap around from 255 to 0
           // because of integer overflow! This happens to also be the range of values for
           // an 8-bit color pixel. This optimization makes our code simpler and many times
           // faster. Although we're only powering 2 leds in this case, when you're powering
           // several hundred of them, this makes a big difference.

           // the FastLED library has lots of other functions that make use of 8-bit integers
           // (and 16 bit). These include saturating arithmetic (100 + 200 = 255 instead of 
           // overflowing) and fast 8-bit trig functions. Take a look at 
           // https://github.com/FastLED/FastLED/wiki/High-performance-math for documentation
           // on these functions, and https://github.com/rdudhagra/Sand-Table/blob/master/Light%20Strip%20Controller/main/colorpulse.h,
           // (from one of my projects) for how these functions can do something quite complicated
           // on a fairly weak processor (that example also runs on an Arduino Uno)
  delay(10);
}
