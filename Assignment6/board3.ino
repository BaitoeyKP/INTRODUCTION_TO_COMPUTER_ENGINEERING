#include <Wire.h>
char message[7];

void setup() {
  Wire.begin(3);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Serial.begin(9600);
}

void loop() {}

void receiveEvent(int bytes) {
  for (int i = 0; i < bytes && i < 6; i++) {
    message[i] = Wire.read();
  }
  message[5] = (message[5] - '0') % 9 + '1';
}

void requestEvent() {
  Wire.write(message);
  Serial.println(message);
}
