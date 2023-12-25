const int analogPhPin = 26;  //PH module pin P0 connected to analog pin A0
// const int analogPhPintem = 27;
long phTot;
float phAvg;
int x;
float C = 25.85;  //Constant of straight line (Y = mx + C)
float m = -6.80;  // Slope of straight line (Y = mx + C)

void setup() {

  // sensors.begin(); //Start the DS18B20 Library
  Serial.begin(115200);
  // analogReadResolution(12);
}
void loop() {
  phTot = 0;
  // temTot = 0;
  phAvg = 0;
  // temAvg = 0;

  // taking 10 sample and adding with 10 milli second delay
  for (x = 0; x < 10; x++) {
    phTot += analogRead(analogPhPin);
    // temTot += analogRead(analogPhPintem);
    delay(10);
  }
  // float temAvg = temTot / 10;

  float phAvg = phTot / 10;

  // phTot = analogRead(analogPhPin);
  // temTot = analogRead(analogPhPintem);

  // Serial.print("phTot = ");
  // Serial.print(phTot);
  // Serial.print("  temTot = ");
  // Serial.print(temTot);
  // Serial.print(" ************ ");

  // float temVoltage = temAvg * (5000.0 / 1023.0); //convert sensor reading into milli volt
  float phVoltage = phAvg * (3.3 / 4095.0);  //convert sensor reading into milli volt


  // float Etemp = temVoltage*0.1; //convert milli volt to temperature degree Celsius
  float pHValue = phVoltage * m + C;

  Serial.print("phVoltage = ");
  Serial.print(phVoltage);
  Serial.print(" *** ");
  Serial.print("pH = ");
  Serial.println(pHValue);

  delay(1000);
}