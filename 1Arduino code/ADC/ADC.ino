
const int sensorPin = A4;
int sensorvalue1, sensorvalue;
float voltagevalue = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  analogReadResolution(12);
}

void loop() {
  sensorvalue = 0;
  sensorvalue1 = 0;
  for (int x = 0; x < 10; x++) {
    sensorvalue1 += analogRead(sensorPin);
    delay(10);
  }
  sensorvalue = sensorvalue1 / 10;

  // sensorvalue = analogRead(sensorPin);
  voltagevalue = sensorvalue * (3.3 / 4095.0);
  Serial.print("sensor value = ");
  Serial.print(sensorvalue);
  Serial.print("\t");
  Serial.print("voltagevalue = ");
  Serial.println(voltagevalue);
  delay(1000);
}
