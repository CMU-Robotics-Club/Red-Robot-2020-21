#define LEFT_LINE_SENSOR 9
#define RIGHT_LINE_SENSOR 10

void line_sensor_setup() {
  pinMode(LEFT_LINE_SENSOR, INPUT);
  pinMode(RIGHT_LINE_SENSOR, INPUT);
}

int read_left_sensor() {
  return digitalRead(LEFT_LINE_SENSOR);
}

int read_right_sensor() {
  return digitalRead(RIGHT_LINE_SENSOR);
}
