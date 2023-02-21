int number[12][7] =  {{1, 1, 1, 1, 1, 1, 0}, // 0 a b c d e f g
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}, // 9
  {0, 0, 0, 1, 1, 1, 0}, // L
  {1, 0, 1, 1, 1, 1, 0}
}; // G
bool isStarted = false;
int currentNumber = 1;
int realNum = 0;
int randomNum;
int debounceDelay = 50;
int lastADebounce = 0;
int lastBDebounce = 0;
int stateA;
int stateB = LOW;

void setup()
{
  Serial.begin(9600);
  for (int pin = 3; pin < 10; pin++) {
    pinMode(pin, OUTPUT);
  }
  pinMode(12, INPUT); //switch 1 pull up
  pinMode(11, INPUT); //switch 2 pull up
  numWrite(1);
  randomSeed(analogRead(A0));
  randomNum = random(9);
  Serial.println(randomNum);
}

void numWrite(int a)
{
  for (int i = 3; i < 10; i++) {
    if (number[a][i - 3] == 0) {
      digitalWrite(i, HIGH);
    }
    else {
      digitalWrite(i, LOW);
    }
  }
}

void loop() {
  if (digitalRead(12) != stateA) {
    lastADebounce = millis();
  }
  if ((millis() - 0) > debounceDelay) {
    if (digitalRead(12) != stateA) {
      stateA = digitalRead(12);
      if (stateA) {
        isStarted = true;
        realNum = currentNumber;
        numWrite(currentNumber);
        currentNumber = currentNumber + 1;
        if (currentNumber > 9) {
          currentNumber = 1;
        }
        if (realNum > 9) {
          realNum = 0;
        }
      }
    }
  }
  if (digitalRead(11) != stateB) {
    lastBDebounce = millis();
  }
  if ((millis() - 0) > debounceDelay) {
    if (digitalRead(11) != stateB) {
      stateB = digitalRead(11);
      if (stateB && isStarted) {
        if (realNum == randomNum) {
          numWrite(0);
          randomSeed(analogRead(A0));
          randomNum = random(9);
          Serial.println(randomNum);
          currentNumber = 1;
          realNum = 0;
        }
        else if (realNum > randomNum) {
          numWrite(11);
        }
        else {
          numWrite(10);
        }
      }
    }
  }
}
