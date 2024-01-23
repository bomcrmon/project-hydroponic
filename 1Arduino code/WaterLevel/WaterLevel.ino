#define L50 4
#define L100 2
#define AL50 19
#define AL100 18
// #define L150 14
bool lit50, lit100, alit50, alit100;

void setup() {
  pinMode(L50, INPUT_PULLUP);
  pinMode(L100, INPUT_PULLUP);
  pinMode(AL50, INPUT_PULLUP);
  pinMode(AL100, INPUT_PULLUP);
  // pinMode(L150, INPUT_PULLDOWN);
  Serial.begin(115200);
}

void LevelWater(bool &index, int x) {
  index = digitalRead(x);
  Serial.print(index);
  Serial.print(" ");
}

void loop() {
  LevelWater(lit50, L50);
  LevelWater(lit100, L100);
  LevelWater(alit50, AL50);
  LevelWater(alit100, AL100);
  Serial.println(" ");
  delay(500);
}
