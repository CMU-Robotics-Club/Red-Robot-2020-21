void setup() {
//  Serial.begin(9600);
  move_setup();
  set_speed(1);
}

void loop() {
  forward();
  delay(1000);
  stop();
  delay(100);

  backward();
  delay(1000);
  stop();
  delay(100);
  
  sharp_left();
  delay(1000);
  stop();
  delay(100);
  
  sharp_right();
  delay(1000);
  stop();
  delay(100);
  
  pivot_left();
  delay(1000);
  stop();
  delay(100);
  
  pivot_right();
  delay(1000);
  stop();
  delay(100);
}
