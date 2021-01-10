#include <Servo.h>
#include <FastLED.h>

void setup() {
  Serial.begin(115200);
  claw_setup();
  move_setup();

  set_speed(1);
}

void loop() {
  process_input(); // We run this as fast as possible so that we always have the lastest commands from the bluetooth controller

  EVERY_N_MILLISECONDS(50) { // Run every so often to update servo
      int vl, vr;
      get_speeds(&vl, &vr);
//      Serial.print(vl);
//      Serial.print(" ");
//      Serial.println(vr);
      
      move_robot(vl, vr);
  }
}
