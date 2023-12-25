// #define LED 2
#define water 33
#define moter 25
#define pump 26
#define pump2 27
#define pump3 14

void setup() {
  Serial.begin(115200);
  pinMode(water, INPUT_PULLDOWN);
  // pinMode(LED, OUTPUT);
  pinMode(moter, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(pump2, OUTPUT);
  pinMode(pump3, OUTPUT);
}

void WaterLevel() {
  //ควบุมระดับน้ำ เปิดน้ำเมื่อลดต่ำกว่ากำหนด
  if (digitalRead(water) == 0) {
    digitalWrite(moter, LOW);
    digitalWrite(pump, LOW);

  } else if (digitalRead(water) > 0) {
    digitalWrite(moter, HIGH);
    digitalWrite(pump, HIGH);
  }
}

void waterpump(int i) {
  //ควบคุม Relay
  digitalWrite(i, LOW);
  // digitalWrite(j, LOW);
  Serial.println("on");
  delay(1000);

  digitalWrite(i, HIGH);
  // digitalWrite(j, 1);
  Serial.println("off");
  delay(1000);
}

void loop() {
  Serial.println(digitalRead(water));
  WaterLevel();
  delay(100);
  // waterpump(pump2);
  // waterpump(pump3);




  // digitalWrite(LED, HIGH);
  // delay(500);
  // digitalWrite(LED, LOW);
}