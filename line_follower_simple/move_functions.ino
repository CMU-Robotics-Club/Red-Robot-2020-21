#define IN1_PIN 6
#define IN2_PIN 7
#define IN3_PIN 5
#define IN4_PIN 4

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

void move_robot(float leftSpeed, float rightSpeed) {
  // Move function: leftSpeed and rightSpeed from -1 to 1, 0 is no movement
  leftSpeed = constrain(leftSpeed, -1, 1);
  rightSpeed = constrain(rightSpeed, -1, 1);

  leftSpeed *= speed_multiplier;
  rightSpeed *= speed_multiplier;

  leftSpeed *= 255; // get into range of analogWrite
  rightSpeed *= 255;

  float pin1 = 0, pin3 = 0;
  int pin2 = 0, pin4 = 1;

  if(leftSpeed > 0) pin1 = leftSpeed;
  else {
    pin1 = -1 * leftSpeed;
    pin2 = 1;
  }

  if(rightSpeed > 0) pin3 = rightSpeed;
  else {
    pin3 = -1 * rightSpeed;
    pin4 = 0;
  }

  analogWrite(IN1_PIN, (int)pin1);
  digitalWrite(IN2_PIN, (int)pin2);
  analogWrite(IN3_PIN, (int)pin3);
  digitalWrite(IN4_PIN, (int)pin4);
}

void set_speed(float speed) {
  // speed is a float between 0 and 1
  speed_multiplier = constrain(speed, 0, 1);
}

void forward() {
  move_robot(1, 1);
}

void backward() {
  move_robot(-1, -1);
}

void stop() {
  move_robot(0, 0);
}

void sharp_left() {
  move_robot(-1, 1);
}

void sharp_right() {
  move_robot(1, -1);
}

void pivot_left() {
  move_robot(0 , 1);
}

void pivot_right() {
  move_robot(1, 0);
}
