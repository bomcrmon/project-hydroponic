#define waterSensor A13
#define led 32
int val = 0;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(waterSensor, INPUT);
  Serial.begin(115200);
}

void loop() {
  val = analogRead(waterSensor);
  Serial.println(val);
  if (val > 1000) {
    digitalWrite(led, LOW);
  } else {
    digitalWrite(led, HIGH);
  }
  delay(1000);
}
