#define NOTE_C  523
#define NOTE_CS 555
#define NOTE_D  587
#define NOTE_DS 623
#define NOTE_E  658
#define NOTE_F  698
#define NOTE_FS 741
#define NOTE_G  784
#define NOTE_GS 832
#define NOTE_A  880
#define NOTE_AS 934
#define NOTE_B  988

#define NOTE_OPEN_CLAW 494

#define BUZZER_PIN 8

void playTone(int hz, int duration) {
  if(hz == NOTE_OPEN_CLAW) {
    open_claw(); // Don't play the tone, open claw instead
    return;
  }
  
  tone(BUZZER_PIN, hz);
  FastLED.delay(duration);
  noTone(BUZZER_PIN);
}
