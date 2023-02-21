const int LED_1 = 11;
const int LED_2 = 9;
const int LED_3 = 7;
void setup()
{
}
void loop()
{
  //LED 1
  pinMode(LED_1, OUTPUT);
  digitalWrite(LED_1, LOW);
  pinMode(LED_2, OUTPUT);
  digitalWrite(LED_2, HIGH);
  pinMode(LED_3, INPUT);
  digitalWrite(LED_3, LOW);
  delay(1000);

  //LED 2
  pinMode(LED_1, OUTPUT);
  digitalWrite(LED_1, HIGH);
  pinMode(LED_2, OUTPUT);
  digitalWrite(LED_2, LOW);
  pinMode(LED_3, INPUT);
  digitalWrite(LED_3, LOW);
  delay(1000);

  //LED 3
  pinMode(LED_1, INPUT);
  digitalWrite(LED_1, LOW);
  pinMode(LED_2, OUTPUT);
  digitalWrite(LED_2, LOW);
  pinMode(LED_3, OUTPUT);
  digitalWrite(LED_3, HIGH);
  delay(1000);

  //LED 4
  pinMode(LED_1, INPUT);
  digitalWrite(LED_1, LOW);
  pinMode(LED_2, OUTPUT);
  digitalWrite(LED_2, HIGH);
  pinMode(LED_3, OUTPUT);
  digitalWrite(LED_3, LOW);
  delay(1000);

  //LED 5
  pinMode(LED_1, OUTPUT);
  digitalWrite(LED_1, LOW);
  pinMode(LED_2, INPUT);
  digitalWrite(LED_2, LOW);
  pinMode(LED_3, OUTPUT);
  digitalWrite(LED_3, HIGH);
  delay(1000);

  //LED 6
  pinMode(LED_1, OUTPUT);
  digitalWrite(LED_1, HIGH);
  pinMode(LED_2, INPUT);
  digitalWrite(LED_2, LOW);
  pinMode(LED_3, OUTPUT);
  digitalWrite(LED_3, HIGH);
  digitalWrite(LED_3, LOW);
  delay(1000);

  //LED 5
  pinMode(LED_1, OUTPUT);
  digitalWrite(LED_1, LOW);
  pinMode(LED_2, INPUT);
  digitalWrite(LED_2, LOW);
  pinMode(LED_3, OUTPUT);
  digitalWrite(LED_3, HIGH);
  delay(1000);

  //LED 4
  pinMode(LED_1, INPUT);
  digitalWrite(LED_1, LOW);
  pinMode(LED_2, OUTPUT);
  digitalWrite(LED_2, HIGH);
  pinMode(LED_3, OUTPUT);
  digitalWrite(LED_3, LOW);
  delay(1000);

  //LED 3
  pinMode(LED_1, INPUT);
  digitalWrite(LED_1, LOW);
  pinMode(LED_2, OUTPUT);
  digitalWrite(LED_2, LOW);
  pinMode(LED_3, OUTPUT);
  digitalWrite(LED_3, HIGH);
  delay(1000);

  //LED 2
  pinMode(LED_1, OUTPUT);
  digitalWrite(LED_1, HIGH);
  pinMode(LED_2, OUTPUT);
  digitalWrite(LED_2, LOW);
  pinMode(LED_3, INPUT);
  digitalWrite(LED_3, LOW);
  delay(1000);
}
