#define PHSensorPin 34
int AnalogValue;
double VoltageInput;
float PHvalue;
void setup() {
  Serial.begin(9600);
  delay(100);
}
void loop() {
  AnalogValue = analogRead(PHSensorPin);
  Serial.print("Analog Value Input = ");
  Serial.println(AnalogValue);
  VoltageInput = 5 / 1024.0 * AnalogValue;
  Serial.print("Volatge = ");
  Serial.println(VoltageInput, 3);
  PHvalue = PHvalue = 7 + ((3.78 - VoltageInput) / 0.28);
  Serial.print("PH Value : ");
  Serial.println(PHvalue, 3);
  Serial.println(" ");
  delay(3000);
}
