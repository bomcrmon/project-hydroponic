#define waterSensor 15
#define led 32
int sensorValue = 0;
bool re1state,re2state;

void setup() {
  pinMode(led, OUTPUT);
  // pinMode(waterSensor, INPUT);
  Serial.begin(115200);
}
void WaterSensor() {
  sensorValue = analogRead(waterSensor);
  float waterLevel = map(sensorValue, 0, 3100, 0, 100);
  Serial.printf("WaterLevel --> ");
  Serial.print(String(waterLevel));
  Serial.println("%");

  if (waterLevel > 50) {
    digitalWrite(led, LOW);
    Serial.println("re1 on");
    re1state = true;
  } else {
    digitalWrite(led, HIGH);
    Serial.println("re1 off");
    re1state = false;
  }
}

void loop() {
  WaterSensor();
  // val = analogRead(waterSensor);
  // Serial.printf("WaterSensor --> ");
  // Serial.println(val);
  // if (val > 1000) {
  //   digitalWrite(led, LOW);
  // } else {
  //   digitalWrite(led, HIGH);
  // }
  delay(1000);
}
