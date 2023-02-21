#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 OLED(OLED_RESET);
#define st 6   //stopwatch
#define buttonSave 3  //save
#define hs 4  //set hour
#define ms 5  //set hour
int sensorPin = A0;
int sensorValue = 0;
byte h;
byte m;
byte s;
int flag;
int timerMode = 0;
long startTime;
int Time;
int mn;
int sec;

void setup()
{
  Serial.begin(9600);
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  OLED.clearDisplay();
  pinMode(hs, INPUT);
  pinMode(ms, INPUT);
  pinMode(st, INPUT);
  pinMode(buttonSave, INPUT);
  h = EEPROM.read(0);
  m = EEPROM.read(1);
  s = EEPROM.read(2);
  flag = h;
}

void loop()
{
  sensorValue = (analogRead(sensorPin) / 600) + 1;
  Serial.println(sensorValue);
  s = s + 1;
  if (s == 59) {
    s = 0;
    m = m + 1;
  }
  if (m == 59) {
    m = 0;
    h = h + 1;
    flag = flag + 1;
  }
  if (h == 13) {
    h = 1;
  }
  OLED.setTextColor(WHITE);
  OLED.setCursor(0, 0);
  OLED.setTextSize(sensorValue);
  OLED.print(h);
  OLED.print(":");
  OLED.print(m);
  if (flag < 12)  OLED.print(" AM");
  if (flag == 12) OLED.print(" PM");
  if (flag > 12)  OLED.print(" PM");
  if (flag == 24) flag = 0;
  OLED.display();
  delay(1000);
  OLED.clearDisplay();
  if (digitalRead(hs) == LOW) {
    h = h + 1;
    flag = flag + 1;
    if (h == 13) {
      h = 1;
    }
    if (flag == 24) {
      flag = 0;
    }
  }
  if (digitalRead(ms) == LOW) {
    m = m + 1;
  }
  //stopwatch
  OLED.setCursor(0, 15);
  if (digitalRead(st) == LOW) {
    startTime = millis();
    timerMode++;
    delay(400);
  }
  if (timerMode == 1) {
    OLED.setCursor(0, 25);
    OLED.setTextSize(1);
    OLED.print("STOPWATCH:");
    Time = (millis() - startTime) / 1000.0;
    sec = Time % 60;
    OLED.print(mn);
    OLED.print(":");
    OLED.print(sec);
    if (sec == 59) {
      sec = 0;
      mn = mn + 1;
    }
  }
  if (timerMode > 1) {
    delay (1000);
    timerMode = 0;
    mn = 0;
    OLED.clearDisplay();
  }
  //save
  if (digitalRead(buttonSave) == LOW) {
    Serial.println("save");
    EEPROM.update(0, h);
    EEPROM.update(1, m);
    EEPROM.update(2, s);
  }
}
