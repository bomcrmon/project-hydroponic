#define phport 34
// const int phsensor = 27;
long phTot;
float phAvg;
int x;
float C = 25.85;  //Constant of straight line (Y = mx + C)
float m = -6.80;  // Slope of straight line (Y = mx + C)

void setup() {
  pinMode(phport, INPUT_PULLDOWN);
  Serial.begin(115200);
  analogReadResolution(12);
}

void PHsensor() {
  phTot = 0;
  phAvg = 0;

  // taking 10 sample and adding with 10 milli second delay
  for (x = 0; x < 10; x++) {
    phTot += analogRead(phport);
    delay(10);
  }
  float phAvg = phTot / 10;

  float phVoltage = phAvg * (3.3 / 4095.0);
  float pHValue = phVoltage * m + C;

  Serial.print("phVoltage = ");
  Serial.print(phVoltage);
  Serial.print(" ");
  Serial.print("pH=");
  Serial.println(pHValue);

  delay(1000);
}

void loop() {
  PHsensor();
}
