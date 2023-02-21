const int button_1 = 11;
const int button_2 = 10;
const int button_3 = 9;
const int LED_1 = 5;  //Red
const int LED_2 = 4;  //Yellow
const int LED_3 = 3;  //Green

long  time1 = 0, time2 = 0, time3 = 0;
size_t debounce = 200;
int SS1 = 0, SS2 = 0, SS3 = 0;
int i = 0;

void setup() {
  pinMode(button_1, INPUT); //pull down
  pinMode(button_2, INPUT); //pull up
  pinMode(button_3, INPUT_PULLUP);  //pull up
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
}

void loop() {
  int state1 = digitalRead(button_1), state2 = digitalRead(button_2), state3 = digitalRead(button_3);

  //LED1
  if (state1 == 1 && millis() - time1 > debounce) {
    if (!SS1) {
      digitalWrite(LED_1, HIGH);
      SS1 = 1;
    }
    else {
      digitalWrite(LED_1, LOW);
      SS1 = 0;
    }
    time1 = millis();
  }
  if (SS1) {  //delay 3 s
    if (millis() - time1 >= 3000) {
      digitalWrite(LED_1, LOW);
      SS1 = 0;
    }
  }

  //LED2
  if (state2 == 0 && SS1 == 0 && SS3 == 0 && millis() - time2 > debounce) {
    digitalWrite(LED_2, HIGH);
    SS2 = 1;
    time2 = millis();
  }
  if (SS2)
  {
    if (millis() - time2 >= 500) {
      if (i % 2 == 0) {
        digitalWrite(LED_2, LOW);
      }
      else {
        digitalWrite(LED_2, HIGH);
      }
      time2 = millis();
      i++;
    }
    if (i == 3) {
      i = 0;
      SS2 = 0;
    }
  }

  //LED3
  if (state3 == 0 && SS1 == 0 && millis() - time3 > debounce) {
    if (!SS3) {
      digitalWrite(LED_3, HIGH);
      SS3 = 1;
    }
    else {
      digitalWrite(LED_3, LOW);
      SS3 = 0;
    }
    time3 = millis();

  }
  if (SS3)
  {
    if (millis() - time3 >= 3000) {
      digitalWrite(LED_3, LOW);
      SS3 = 0;
    }
  }
}
