#define POLL_FREQUENCY 20
#define MAX_DISTANCE_CM 200
#define MAX_TIME_MCS 20000 // In reality, doesn't take longer than 30ms

#define POLL_NUM 5
#define OUTLIER_THRESH 50

double dist_last = 0;

double get_distance()
{
  double dists[POLL_NUM] {0};
  double dist = 0;

  unsigned long startTime = micros(); // We can assume this won't overflow because we won't be running our robot for anywhere close to 4,294 seconds (1 hr 11 min)

  // Record distance measurements
  for (int i = 0; i < POLL_NUM; i++) {
    pinMode(A3, OUTPUT);
    digitalWrite(A3, LOW);
    delayMicroseconds(2000);
    digitalWrite(A3, HIGH);
    delayMicroseconds(10);
    digitalWrite(A3, LOW);
    pinMode(A3, INPUT);
    double d = (double)pulseIn(A3, HIGH, 29000) / 58.0; // Times out for distances > 200cm (using speed of sound)
    dists[i] = d;
    dist += d;

    if (micros() - startTime > MAX_TIME_MCS) {
      // Took too long, just return what we have
      double newDist = dist / (i + 1);
      if (newDist > MAX_DISTANCE_CM) newDist = MAX_DISTANCE_CM; // Any values greater than 200cm are meaningless
      if (newDist == 0) newDist = MAX_DISTANCE_CM;
      dist_last = newDist;
      return newDist;
    }
  }
  // compute avg
  dist /= POLL_NUM;

  // find outliers, calc new average
  double newDist = 0;
  uint8_t numGood = 0;
  for (int i = 0; i < POLL_NUM; i++) {
    if (abs(dists[i] - dist) <= OUTLIER_THRESH) {
      // only include in average if less than OUTLIER_THRESH away from avg
      newDist += dists[i];
      numGood++;
    }
  }
  // compute avg
  newDist /= numGood;

  if (newDist > MAX_DISTANCE_CM) newDist = MAX_DISTANCE_CM; // Any values greater than 200cm are meaningless
  if (newDist == 0) newDist = MAX_DISTANCE_CM;
  dist_last = newDist;
  return newDist;
}

void wait_until_distance(double d) {
  do {
    wait(1000 / POLL_FREQUENCY);
  } while (dist_last > d);
}

void show_dist_on_led() {
  double d = get_distance();
  set_right_led_color(CHSV((uint8_t)constrain(d, 0, 175), 255, 255));
}
