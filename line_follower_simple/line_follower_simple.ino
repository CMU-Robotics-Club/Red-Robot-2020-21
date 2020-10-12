#define WHITE 1
#define BLACK 0

#define LEFT 1
#define RIGHT 0

#define TURN_AMOUNT 0.65
#define SHARP_TURN_AMOUNT 0.85

void setup() {
  move_setup();
  set_speed(1);

  line_sensor_setup();
}

int turning = 0;

void loop() {
  int left = read_left_sensor();
  int right = read_right_sensor();

  if (left == BLACK && right == BLACK)
    forward();
  else if (left == WHITE && right == BLACK) {
    move_robot(1, 1 - TURN_AMOUNT);
    turning = LEFT;
  } else if (left == BLACK && right == WHITE) {
    move_robot(1 - TURN_AMOUNT, 1);
    turning = RIGHT;
  } else if (turning == RIGHT) {
    move_robot(1 - SHARP_TURN_AMOUNT, 1);
  } else if (turning == LEFT) {
    move_robot(1, 1 - SHARP_TURN_AMOUNT);
  } else {
    stop();
  }

  delay(10);
}
