#define LED_PIN     13
#define NUM_LEDS    2
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
#define LEFT_LED 0
#define RIGHT_LED 1

#define UPDATE_RATE 50 // in Hz, decrease if performance is an issue
#define BRIGHTNESS  255 // decrease if the leds are too bright


void led_setup() { // This function must be somewhere in your setup or the LED's will not work
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

void update_leds() { // This function must be somewhere in your loop or the LED's will never update
  EVERY_N_MILLISECONDS(1000 / UPDATE_RATE) { // This is a macro that's part of the FastLED library
    FastLED.show(); // This code will run every (1000 / UPDATE_RATE) milliseconds, as long as it's called
  }                 // often enough in your loop
}

// For information on CRGB and CHSV, see https://github.com/FastLED/FastLED/wiki/Pixel-reference
// tldr it's really easy: 
//    CRGB(red, green, blue) represents an RGB value
//    CHSV(hue, saturation, value (brightness)) represents an HSV value, useful if you want to program a rainbow effect, etc.

void set_left_led_color(CRGB c) { // Set a specific led to a specific color
  leds[LEFT_LED] = c;
}

void set_left_led_color_hsv(CHSV c) { // Set a specific led to a specific color (in HSV space)
  leds[LEFT_LED] = c; // the conversion from CHSV to CRGB is done automatically
}


void set_right_led_color(CRGB c) { // Set a specific led to a specific color
  leds[RIGHT_LED] = c;
}

void set_right_led_color_hsv(CHSV c) { // Set a specific led to a specific color (in HSV space)
  leds[RIGHT_LED] = c; // the conversion from CHSV to CRGB is done automatically
}

void set_led_color(CRGB c) { // Set both leds to the same color
  set_left_led_color(c);
  set_right_led_color(c);
}

void set_led_color_hsv(CHSV c) { // Set both leds to the same color (in hSV space)
  set_left_led_color_hsv(c);
  set_right_led_color_hsv(c);
}
