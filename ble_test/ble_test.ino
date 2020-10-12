#include <FastLED.h>
#include <Servo.h>
#define CUSTOM_SETTINGS
#define INCLUDE_LEDCONTROL_MODULE
#include <Dabble.h>

#define SERVO_PIN 13
Servo servo;

void setup() {
  Serial.begin(9600);
  Dabble.begin(Serial);   // Connect the Dabble controller to hardware serial (where the bluetooth chip is reading from)
  
  servo.attach(SERVO_PIN);
}

void loop() {
  Dabble.processInput(); // We run this as fast as possible so that we always have the lastest commands from the bluetooth controller
  LedControl.readBrightness();

  EVERY_N_MILLISECONDS(100) { // Run every so often to update servo
    int val = LedControl.readBrightness();
    servo.write(map(val, 0, 100, 180, 0));
  }
}
