//#define WHITE 1
//#define BLACK 0
//
//#define LEFT 1
//#define RIGHT 0
//
//#define TURN_AMOUNT 0.925
//#define SHARP_TURN_AMOUNT 1.9
////#define TURN_AMOUNT 0.925
////#define SHARP_TURN_AMOUNT 1.9
//#define NO_LINE_DURATION 50000 // Microseconds to wait before sharp turn
//#define CORNER_CHECK_DURATION 16000
//// #define TURN_AMOUNT 0.65
//// #define SHARP_TURN_AMOUNT 0.85
//
//void setup() {
//  Serial.begin(115200);
//  move_setup();
//  set_speed(0.5);
//  pinMode(13, OUTPUT);
//
//  line_sensor_setup();
//}
//
//int turning = 0;
//bool switchedTurning = false;
//long noLineCounter = 0;
//bool cornerMode = false;
//
//void loop() {
//  long d = 1000;
//  long startTime = micros();
//
//  int left = read_left_sensor();
//  int right = read_right_sensor();
//
//  if (left == BLACK && right == BLACK) {
//    forward();
//    if (switchedTurning) {
////      cornerMode = true;
//    } else {
//      switchedTurning = true;
//      d = CORNER_CHECK_DURATION;
//    }
//    noLineCounter = 0;
//  } else if (left == WHITE && right == BLACK) {
//    if (cornerMode) {
//      d = CORNER_CHECK_DURATION;
//    } else {
//      cornerMode = false;
//      // move_robot(1, 1 - TURN_AMOUNT);
//      forward();
//      turning = LEFT;
//      noLineCounter = 0;
//      switchedTurning = false;
//    }
//  } else if (left == BLACK && right == WHITE) {
//    if (cornerMode) {
//      d = CORNER_CHECK_DURATION;
//    } else {
//      cornerMode = false;
//      move_robot(1 - TURN_AMOUNT, 1);
//      turning = RIGHT;
//      noLineCounter = 0;
//      switchedTurning = false;
//      d = 25000; // Delay a bit longer so we stay centered on the left edge of the line
//    }
//  } else {
////    if (cornerMode && switchedTurning)
////      turning = !turning;
//    cornerMode = false;
//    switchedTurning = false;
//    noLineCounter += d;
//    if (noLineCounter >= NO_LINE_DURATION) {
//      if (turning == RIGHT) {
//        move_robot(1 - SHARP_TURN_AMOUNT, 1);
//      } else {
//        move_robot(1, 1 - SHARP_TURN_AMOUNT);
//      }
//    } else {
//      forward();
//    }
//  }
//  digitalWrite(13, cornerMode);
//
//  //  Serial.println(max(0, d - (micros() - startTime)));
//
//  // We must delay in steps, since delayMicroseconds only accepts unsigned ints
//  long t = min(65535, max(0, d - (long)(micros() - startTime)));
//  do {
//    delayMicroseconds(t);
//    t = min(65535, max(0, d - (long)(micros() - startTime)));
//  } while (t >= 65535);
//}
