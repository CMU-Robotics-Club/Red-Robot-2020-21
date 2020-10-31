#define POLL_FREQUENCY 100
#define MAX_DISTANCE_CM 500

#define POLL_NUM 5
#define OUTLIER_THRESH 50

double get_distance()
{
  double dists[POLL_NUM]{0};
  double dist = 0;

  // Record distance measurements
  for (int i = 0; i < POLL_NUM; i++) {
    pinMode(A3, OUTPUT);
    digitalWrite(A3, LOW);
    delayMicroseconds(2000);
    digitalWrite(A3, HIGH);
    delayMicroseconds(10);
    digitalWrite(A3, LOW);
    pinMode(A3, INPUT);
    double d = (double)pulseIn(A3, HIGH, 29155) / 58.0; // Times out for distances > 500cm (using speed of sound)
    dists[i] = d;
    dist += d;
  }
  // compute avg
  dist /= POLL_NUM;

  // find outliers, calc new average
  double newDist = 0;
  uint8_t numGood = 0;
  for (int i = 0; i < POLL_NUM; i++) {
    if(abs(dists[i] - dist) <= OUTLIER_THRESH) {
      // only include in average if less than OUTLIER_THRESH away from avg
      newDist += dists[i];
      numGood++;
    }
  }
  // compute avg
  newDist /= numGood;
  
  if (newDist > MAX_DISTANCE_CM) newDist = INFINITY; // Any values greater than 500cm are meaningless
  return newDist;
}
