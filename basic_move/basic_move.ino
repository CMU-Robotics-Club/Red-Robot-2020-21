#define LEFT_STEP 6
#define LEFT_DIR 7
#define RIGHT_STEP 5
#define RIGHT_DIR 4

void setup() {
  pinMode(LEFT_STEP, OUTPUT);
  pinMode(LEFT_DIR, OUTPUT);
  pinMode(RIGHT_STEP, OUTPUT);
  pinMode(RIGHT_DIR, OUTPUT);
}

void loop() {
  // Forward
  analogWrite(LEFT_STEP, 100);
  digitalWrite(LEFT_DIR, LOW);
  analogWrite(RIGHT_STEP, 100);
  digitalWrite(RIGHT_DIR, HIGH);
  delay(1000);
}
