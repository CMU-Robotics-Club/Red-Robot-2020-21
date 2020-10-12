#include <FastLED.h>
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

#define SPEED_MULTIPLIER 1.25

void setup() {
  Serial.begin(9600);
  Dabble.begin(Serial);   // Connect the Dabble controller to hardware serial (where the bluetooth chip is reading from)

  move_setup();
  set_speed(1);
}

void loop() {
  Dabble.processInput(); // We run this as fast as possible so that we always have the lastest commands from the bluetooth controller

  EVERY_N_MILLISECONDS(50) { // Run every so often to update servo
    if(GamePad.isUpPressed()) {
      forward();
    } else if(GamePad.isDownPressed()) {
      backward();
    } else if(GamePad.isLeftPressed()) {
      pivot_left();
    } else if(GamePad.isRightPressed()) {
      pivot_right();
    } else {
      // Use joystick values
      float x = GamePad.getXaxisData() / 7.0;
      float y = GamePad.getYaxisData() / 7.0;

      float vl, vr;
      joystick_to_wheel_speeds(x, y, &vl, &vr);
      set_speed(vl * SPEED_MULTIPLIER, vr * SPEED_MULTIPLIER);
    }
  }
}
