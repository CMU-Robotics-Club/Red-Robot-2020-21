// Variables that store controller information
int left_speed = 0;
int right_speed = 0;

// Variables to store incoming data
/*
  Protocol:
  ff 55 len idx action device port slot data
  0  1  2   3   4      5      6    7    8
*/
const uint8_t buflen = 52;
byte buf[buflen];
uint8_t index = 0;
uint8_t dataLen;

void process_input() {
  while (Serial.available()) {
    buf[index] = Serial.read();

    switch (index) {
      // Check that the two first bits are 0xff and 0x55 respectively
      case 0:
        if (buf[0] != 0xff) {
          index = 0; // Invalid message, reset buffer
          continue;
        }
        break;
      case 1:
        if (buf[1] != 0x55) {
          index = 0; // Invalid message, reset buffer
          continue;
        }
        break;

      // The third bit contains the length of the data portion of the message
      case 2:
        dataLen = buf[index]; // cap the data length so that the total length of the message cannot exceed the length of the buffer
        break;

      default:
        dataLen--;
        // Check if we get the start sequence, and if we should reset the buffer
        if (buf[index] == 0x55 && buf[index - 1] == 0xff) {
          buf[0] = 0xff;
          buf[1] = 0x55;
          index = 2;
          continue;
        }
        break;
    }

    index++;
    if (index > 51)
      index = 0; // Invalid message
    else if (dataLen == 0 && index > 3) {
      parse_data();
      index = 0;
    }

  }
}

void parse_data() {
//  print_buffer();
  if (buf[4] == 1) { // GET value from robot
    if (buf[5] == 0) { // GET firmware version
      // We will send the string below to trick the app into thinking we're legit firmware
      write_head();
      Serial.write(buf[3]);
      Serial.write("\x04\x09");
      Serial.write("06.01.107");
      write_end();
    }
  } else if (buf[4] == 2) { // COMMAND from phone app
    if (buf[5] == 5) { // Joystick command
      // The left/right speeds are encoded in positions 6-7 and 8-9 in the buffer
      left_speed = -1 * (buf[6] + (buf[7] << 8));
      right_speed = buf[8] + (buf[9] << 8);
    }
  }
}

void write_head() {
  Serial.write(0xff);
  Serial.write(0x55);
}

void write_end() {
  Serial.println();
}

void print_buffer() {
  for (int i = 0; i < 52; i++) {
    Serial.print(buf[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}

void get_speeds(int *vl, int *vr) {
  *vl = left_speed;
  *vr = right_speed;
}
