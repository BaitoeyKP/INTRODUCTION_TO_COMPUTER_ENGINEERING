#include <Wire.h>
char message[7] = "HELLO1";
bool numSlave = true;

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  numSlave = !numSlave;
  Wire.beginTransmission(numSlave + 2);
  Wire.write(message);
  Wire.endTransmission();
  int request = Wire.requestFrom(numSlave + 2, 6);
  for (int i = 0; i < request; i++) {
    message[i] = Wire.read();
  }
  Serial.println(message);
  delay(1000);
}
