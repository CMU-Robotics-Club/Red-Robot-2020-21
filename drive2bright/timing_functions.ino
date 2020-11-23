#define LOOP_TIME_MCS 50000

// We use this instead of delay because there are things that we need to run constantly. If we use delay, we won't be able to do that.
// Instead, this function will wait for a certain period of time, like delay, but still run update functions during that interval.

// Don't use this function for delays shorter than 50ms...it won't be fast enough
void wait(unsigned long ms) {
  unsigned long startTime = micros(); // We can assume this won't overflow because we won't be running our robot for anywhere close to 4,294 seconds (1 hr 11 min)

  unsigned long mcs = ms * 1000;
  unsigned long newTime;
  unsigned long loopTime;
  unsigned long remainingTime = mcs;
  unsigned long remainingTimeInLoop;
  bool returnFlag;

  unsigned long currTime = micros();
  while (remainingTime > 0) {
    // Functions to run constantly
    //show_dist_on_led(); // Set the right LED color to match the data from the ultrasonic sensor
    //update_leds(); // Update the RGB Leds on the robot

    // Timing stuff
    newTime = micros();
    loopTime = newTime - currTime;
    currTime = newTime;

    remainingTime = mcs - (currTime - startTime);
    if (remainingTime > mcs)
      remainingTime = 0;

    remainingTimeInLoop = LOOP_TIME_MCS - loopTime;
    if (remainingTimeInLoop > LOOP_TIME_MCS)
      remainingTimeInLoop = 0;

    returnFlag = (remainingTime <= remainingTimeInLoop);
    if (returnFlag) {
      delayMicroseconds(remainingTime);
      return;
    } else {
      delayMicroseconds(remainingTimeInLoop);
    }
  }
}
