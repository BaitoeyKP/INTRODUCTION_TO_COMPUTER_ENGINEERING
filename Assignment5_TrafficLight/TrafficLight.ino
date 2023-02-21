#define LED_W_R 6
#define LED_W_Y 7
#define LED_W_G 8
#define WEST_BUTTON_PIN 5
#define LED_S_R 9
#define LED_S_Y 10
#define LED_S_G 11
#define SOUTH_BUTTON_PIN 4
#define LED_WALK_R 12
#define LED_WALK_G 13
#define WALK_BUTTON_PIN 3

#define goW 0       //  00110010 West เขียว  South แดง   Walk แดง
#define waitW 1     //  01010010 West เหลือง South แดง   Walk แดง
#define goS 2       //  10000110 West แดง   South เขียว  Walk แดง
#define waitS 3     //  10001010 West แดง   South เหลือง Walk แดง
#define goWk 4      //  10010001 West แดง   South แดง   Walk เขียว
#define blink1 5    //  10010000 West แดง   South แดง   Walk ดับ
#define blink2 6    //  10010010 West แดง   South แดง   Walk เขียว
#define blink3 7    //  10010000 West แดง   South แดง   Walk ดับ
#define blink4 8    //  10010010 West แดง   South แดง   Walk เขียว
#define blink5 9    //  10010000 West แดง   South แดง   Walk ดับ
#define blink6 10   //  10010010 West แดง   South แดง   Walk เขียว

struct State {
  unsigned long ST_Out;   // 6-bit pattern to street output
  unsigned long Time;     // delay in msunits
  unsigned long Next[8];  // next state for inputs 0,1,2,3,4,5,6,7
};
typedef const struct State SType;
// 0        1       2       3      4        5       6       7
//000      100     010     110    001      101     011     111
SType FSM[11] = {{B00110010, 5000, {goW,    waitW,  waitW,  waitW,  goW,    waitW,  waitW,  waitW}},  //0  goW    -> 00110010 West เขียว  South แดง   Walk แดง
  {B01010010, 3000, {goS,    goWk,   goS,    goS,    goS,    goWk,   goS,    goS}},    //1  waitW  -> 01010010 West เหลือง South แดง   Walk แดง
  {B10000110, 5000, {goS,    waitS,  goS,    waitS,  waitS,  waitS,  waitS,  waitS}},  //2  goS    -> 10000110 West แดง   South เขียว  Walk แดง
  {B10001010, 3000, {goWk,   goWk,   goWk,   goWk,   goW,    goWk,   goW,    goWk}},   //3  waitS  -> 10001010 West แดง   South เหลือง Walk แดง
  {B10010001, 5000, {goWk,   goWk,   blink1, blink1, blink1, blink1, blink1, blink1}}, //4  goWk   -> 10010001 West แดง   South แดง   Walk เขียว
  {B10010000, 500,  {blink2, blink2, blink2, blink2, blink2, blink2, blink2, blink2}}, //5  blink1 -> 10010000 West แดง   South แดง   Walk ดับ
  {B10010001, 500,  {blink3, blink3, blink3, blink3, blink3, blink3, blink3, blink3}}, //6  blink2 -> 10010001 West แดง   South แดง   Walk เขียว
  {B10010000, 500,  {blink4, blink4, blink4, blink4, blink4, blink4, blink4, blink4}}, //7  blink3 -> 10010000 West แดง   South แดง   Walk ดับ
  {B10010001, 500,  {blink5, blink5, blink5, blink5, blink5, blink5, blink5, blink5}}, //8  blink4 -> 10010001 West แดง   South แดง   Walk เขียว
  {B10010000, 500,  {blink6, blink6, blink6, blink6, blink6, blink6, blink6, blink6}}, //9  blink5 -> 10010000 West แดง   South แดง   Walk ดับ
  {B10010001, 500,  {goW,    goW,    goS,    goS,    goW,    goW,    goW,    goW}}     //10 blink6 -> 10010001 West แดง   South แดง   Walk เขียว
};


unsigned long S = 0; //index to the current state

void setup() {
  pinMode(LED_W_R, OUTPUT);
  pinMode(LED_W_Y, OUTPUT);
  pinMode(LED_W_G, OUTPUT);
  pinMode(WEST_BUTTON_PIN, INPUT);
  pinMode(LED_S_R, OUTPUT);
  pinMode(LED_S_Y, OUTPUT);
  pinMode(LED_S_G, OUTPUT);
  pinMode(SOUTH_BUTTON_PIN, INPUT);
  pinMode(LED_WALK_R, OUTPUT);
  pinMode(LED_WALK_G, OUTPUT);
  pinMode(WALK_BUTTON_PIN, INPUT);
  Serial.begin(9600);
}

int input, input1, input2, input3;

void loop() {
  digitalWrite(LED_W_R,    FSM[S].ST_Out & B10000000);
  digitalWrite(LED_W_Y,    FSM[S].ST_Out & B01000000);
  digitalWrite(LED_W_G,    FSM[S].ST_Out & B00100000);
  digitalWrite(LED_S_R,    FSM[S].ST_Out & B00010000);
  digitalWrite(LED_S_Y,    FSM[S].ST_Out & B00001000);
  digitalWrite(LED_S_G,    FSM[S].ST_Out & B00000100);
  digitalWrite(LED_WALK_R, FSM[S].ST_Out & B00000010);
  digitalWrite(LED_WALK_G, FSM[S].ST_Out & B00000001);
  delay(FSM[S].Time);

  input1 = digitalRead(WALK_BUTTON_PIN);
  input2 = digitalRead(SOUTH_BUTTON_PIN);
  input3 = digitalRead(WEST_BUTTON_PIN);
  input = (input3 * 4) + (input2 * 2) + input1;

  Serial.print(input1);
  Serial.print(input2);
  Serial.print(input3);
  Serial.println(input);

  S = FSM[S].Next[input];
}
