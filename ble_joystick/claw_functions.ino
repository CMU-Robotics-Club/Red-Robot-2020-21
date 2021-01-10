#define SERVO_PIN 11
#define CLAW_POS_INCR 10

#define MIN_CLAW 5
#define MAX_CLAW 80

int claw_pos;

Servo claw;

void claw_setup() {
  claw_pos = MIN_CLAW;
  claw.attach(SERVO_PIN);
  claw.write(claw_pos);
}

void open_claw() {
  claw_pos = constrain(claw_pos - CLAW_POS_INCR, MIN_CLAW, MAX_CLAW);
  claw.write(claw_pos);
}

void close_claw() {
  claw_pos = constrain(claw_pos + CLAW_POS_INCR, MIN_CLAW, MAX_CLAW);
  claw.write(claw_pos);
}
