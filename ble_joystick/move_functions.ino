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

void move_robot(int leftSpeed, int rightSpeed) {
  // Move function: leftSpeed and rightSpeed from -255 to 255, 0 is no movement
  leftSpeed = (int)((float)leftSpeed * speed_multiplier);
  rightSpeed = (int)((float)rightSpeed * speed_multiplier);

  leftSpeed = constrain(leftSpeed, -255, 255);
  rightSpeed = constrain(rightSpeed, -255, 255);

  int pin1 = 0, pin3 = 0;
  int pin2 = LOW, pin4 = HIGH;

  if (leftSpeed > 0) pin1 = leftSpeed;
  else {
    pin1 = -1 * leftSpeed;
        pin2 = HIGH;
  }

  if (rightSpeed > 0) pin3 = rightSpeed;
  else {
    pin3 = -1 * rightSpeed;
        pin4 = LOW;
  }

  Serial.print(pin1);
  Serial.print("_");
  Serial.print(pin2);
  Serial.print("_");
  Serial.print(pin3);
  Serial.print("_");
  Serial.println(pin4);

  analogWrite(IN1_PIN, pin1);
  digitalWrite(IN2_PIN, pin2);
  analogWrite(IN3_PIN, pin3);
  digitalWrite(IN4_PIN, pin4);
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
