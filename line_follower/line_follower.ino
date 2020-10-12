#define WHITE 1
#define BLACK 0

#define LEFT 0
#define RIGHT 1
#define SHARP_LEFT 2
#define SHARP_RIGHT 3

#define TURN_AMOUNT 0.35
#define SHARP_TURN_AMOUNT 0.9

#define TIME_TO_FLIP 500000 // In microseconds
#define LAST_BLACK_TIME 250000

void setup() {
  Serial.begin(115200);
  move_setup();
  set_speed(1);
  pinMode(13, OUTPUT);

  line_sensor_setup();
}

int current_mode = RIGHT;
bool corner_mode = false;
long last_flip = micros();
long last_black = 0;

void loop() {
  long d = 1000;
  long current_time = micros();
  int prev_mode = current_mode;

  int left = read_left_sensor();
  int right = read_right_sensor();

  if (left == WHITE && right == WHITE) {
    if (current_time - last_flip > TIME_TO_FLIP) {
      if (current_mode <= RIGHT) {
        if (current_time - last_black < LAST_BLACK_TIME + TIME_TO_FLIP) {
          move_robot(0.5 - SHARP_TURN_AMOUNT, 0.35);
          current_mode = SHARP_LEFT;
          corner_mode = true;
        } else {
          move_robot(0.35, 0.5 - SHARP_TURN_AMOUNT);
          current_mode = SHARP_RIGHT;
          corner_mode = true;
        }
      }
    } else {
      move_robot(0.7, 0.7 - TURN_AMOUNT);
      current_mode = RIGHT;
    }
  } else if (left == WHITE && right == BLACK) {
    move_robot(0.7 - TURN_AMOUNT, 0.7);
    current_mode = LEFT;
    corner_mode = false;
  } else if (left == BLACK && right == BLACK) {
    if (current_mode <= RIGHT) {
      last_black = current_time;
      move_robot(0.5, 0.5); // forward
    }
  } else {
    //    move_robot(0.5 - TURN_AMOUNT, 0.5);
    //    current_mode = LEFT;
  }

  if (!corner_mode && prev_mode != current_mode) {
    Serial.println(current_time - last_flip);
    last_flip = current_time;
  }

  //  Serial.println(max(0, d - (micros() - startTime)));

  // We must delay in steps, since delayMicroseconds only accepts unsigned ints
  long t = min(65535, max(0, d - (long)(micros() - current_time)));
  do {
    delayMicroseconds(t);
    t = min(65535, max(0, d - (long)(micros() - current_time)));
  } while (t >= 65535);
}
