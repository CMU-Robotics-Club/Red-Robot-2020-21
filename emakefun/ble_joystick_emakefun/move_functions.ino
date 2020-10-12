#define IN1_PIN 6
#define IN2_PIN 10
#define IN3_PIN 5
#define IN4_PIN 9

float speed_multiplier = 1; // Max speed = 1, min speed = 0

void move_setup() {
  pinMode(IN1_PIN, OUTPUT);
  digitalWrite(IN1_PIN, LOW); // When not sending PWM, we want it low
  pinMode(IN2_PIN, OUTPUT);
  digitalWrite(IN2_PIN, LOW); // When not sending PWM, we want it low
  pinMode(IN3_PIN, OUTPUT);
  digitalWrite(IN3_PIN, LOW); // When not sending PWM, we want it low
  pinMode(IN4_PIN, OUTPUT);
  digitalWrite(IN4_PIN, LOW); // When not sending PWM, we want it low
}

void set_speed(float leftSpeed, float rightSpeed) {
  // Move function: leftSpeed and rightSpeed from -1 to 1, 0 is no movement
  leftSpeed = constrain(leftSpeed, -1, 1);
  rightSpeed = constrain(rightSpeed, -1, 1);

  leftSpeed *= 255; // get into range of analogWrite
  rightSpeed *= 255;

  float pin1 = 0, pin2 = 0, pin3 = 0, pin4 = 0;

  if(leftSpeed > 0) pin2 = leftSpeed;
  else pin1 = -1 * leftSpeed;

  if(rightSpeed > 0) pin3 = rightSpeed;
  else pin4 = -1 * rightSpeed;

  analogWrite(IN1_PIN, (int)pin1);
  analogWrite(IN2_PIN, (int)pin2);
  analogWrite(IN3_PIN, (int)pin3);
  analogWrite(IN4_PIN, (int)pin4);
}

void set_speed(float speed) {
  // speed is a float between 0 and 1
  speed_multiplier = constrain(speed, 0, 1);
}

void forward() {
  set_speed(speed_multiplier, speed_multiplier);
}

void backward() {
  set_speed(-speed_multiplier, -speed_multiplier);
}

void stop() {
  set_speed(0, 0);
}

void sharp_left() {
  set_speed(-speed_multiplier, speed_multiplier);
}

void sharp_right() {
  set_speed(speed_multiplier, -speed_multiplier);
}

void pivot_left() {
  set_speed(0 , speed_multiplier);
}

void pivot_right() {
  set_speed(speed_multiplier, 0);
}
