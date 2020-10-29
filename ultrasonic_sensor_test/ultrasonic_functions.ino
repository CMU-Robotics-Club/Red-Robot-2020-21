double get_distance()
{
  pinMode(A3, OUTPUT);
  digitalWrite(A3, LOW);
  delayMicroseconds(2);
  digitalWrite(A3, HIGH);
  delayMicroseconds(10);
  digitalWrite(A3, LOW);
  pinMode(A3, INPUT);
  return (double)pulseIn(A3, HIGH, 50000 * 55 + 200) / 58.0;
}
