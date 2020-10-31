#include <FastLED.h>

void setup() {
  Serial.begin(115200);
  led_setup();
  line_sensor_setup();
  move_setup();
  set_speed(1);

  delay(1000); // Let stuff warm up

  // Drive forwards towards wall
  drive_to_object(1);
  
  // Turn left 90 deg
  sharp_left_90();
  
  // Drive forwards towards wall
  drive_to_object(0.6);

  // Back into parking space
  sharp_left_45();

  set_speed(0.4);
  backward();
  wait(1250);
  stop();
  wait(250);

  sharp_right_45();
}

void loop() {
  wait(1000);
}

void drive_to_object(float speed) {
  set_speed(speed);
  forward_ramp();
  wait_until_distance(30);
  set_speed(0.4);
  forward();
  wait_until_distance(5);
  stop();
  wait(250);
}

void sharp_left_90() {
  float oldSpeed = get_speed();
  set_speed(0.4);
  sharp_left();
  delay(600);
  stop();
  set_speed(oldSpeed);
  wait(250);
}

void sharp_left_45() {
  float oldSpeed = get_speed();
  set_speed(0.4);
  sharp_left();
  delay(500);
  stop();
  set_speed(oldSpeed);
  wait(250);
}

void sharp_right_45() {
  float oldSpeed = get_speed();
  set_speed(0.4);
  sharp_right();
  delay(500);
  stop();
  set_speed(oldSpeed);
  wait(250);
}
