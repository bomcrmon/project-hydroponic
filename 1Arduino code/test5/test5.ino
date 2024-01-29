#define re1 14
#define re2 12
#define re3 25
#define re4 26
#define re5 27
#define re6 2
#define re7 4
#define re8 5
#define re9 21
#define re10 22
#define re11 23
#define re12 15

void setup() {
  pinMode(re1, OUTPUT);
  pinMode(re2, OUTPUT);
  pinMode(re3, OUTPUT);
  pinMode(re4, OUTPUT);

  pinMode(re5, OUTPUT);
  pinMode(re6, OUTPUT);
  pinMode(re7, OUTPUT);
  pinMode(re8, OUTPUT);

  pinMode(re9, OUTPUT);
  pinMode(re10, OUTPUT);
  pinMode(re11, OUTPUT);
  pinMode(re12, OUTPUT);

  digitalWrite(re1, 1);
  digitalWrite(re2, 1);
  digitalWrite(re3, 1);
  digitalWrite(re4, 1);
  digitalWrite(re5, 1);
  digitalWrite(re6, 1);
  digitalWrite(re7, 1);
  digitalWrite(re8, 1);
  digitalWrite(re9, 1);
  digitalWrite(re10, 1);
  digitalWrite(re11, 1);
  digitalWrite(re12, 1);
}

void loop() {

  digitalWrite(re1, 0);
  digitalWrite(re2, 0);
  digitalWrite(re3, 0);
  digitalWrite(re4, 0);
  digitalWrite(re5, 0);
  digitalWrite(re6, 0);
  digitalWrite(re7, 0);
  digitalWrite(re8, 0);
  digitalWrite(re9, 0);
  digitalWrite(re10, 0);
  digitalWrite(re11, 0);
  digitalWrite(re12, 0);
  delay(10000);
  digitalWrite(re1, 1);
  digitalWrite(re2, 1);
  digitalWrite(re3, 1);
  digitalWrite(re4, 1);
  digitalWrite(re5, 1);
  digitalWrite(re6, 1);
  digitalWrite(re7, 1);
  digitalWrite(re8, 1);
  digitalWrite(re9, 1);
  digitalWrite(re10, 1);
  digitalWrite(re11, 1);
  digitalWrite(re12, 1);
  delay(10000);
}
