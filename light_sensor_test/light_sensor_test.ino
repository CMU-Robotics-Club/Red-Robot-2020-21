#include <FastLED.h>

#define BLACK 0
#define WHITE 1

#define MAX_BRIGHT_THRESH 10
#define FOUND_THRESH 2
#define FINAL_BRIGHTNESS 250

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  move_setup();
  line_sensor_setup();

  delay(1000);
}

void loop() {
  set_speed(0.35);

  int maxBrightness = 0;
  sharp_right();

  int currBrightness = read_light_sensor();
  while (maxBrightness - currBrightness < MAX_BRIGHT_THRESH) {
    currBrightness = read_light_sensor();
    if (currBrightness > maxBrightness)
      maxBrightness = currBrightness;
    delay(25);
  }

  sharp_left();
  while (abs(maxBrightness - currBrightness) > FOUND_THRESH) {
    currBrightness = read_light_sensor();
    delay(25);
  }

  if(maxBrightness > FINAL_BRIGHTNESS) {
    stop();
    while(1);
  }

  set_speed(0.4);

  long startTime = millis();
  while (millis() - startTime < 1000) {
    if (read_left_sensor() == BLACK) {
      move_robot(0, -1);
      delay(1250);
      forward();
      delay(2000);
      break;
    } else if (read_right_sensor() == BLACK) {
      // left sensor is WHITE from above if statement
      move_robot(-1, 0);
      delay(1250);
      forward();
      delay(2000);
      break;
    } else
      forward();
    delay(25);
  }

}
