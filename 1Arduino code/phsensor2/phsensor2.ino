#define phport 32
long phTot;
float phAvg;
int x;
float C = 0;       // Constant of straight line (Y = mx + C)
float m = 4.2424;  // Slope of straight line (Y = mx + C)

void setup() {
  pinMode(phport, INPUT_PULLDOWN);
  Serial.begin(115200);
  analogReadResolution(12);
}

void PHsensor() {
  phTot = 0;
  phAvg = 0;
  float phVoltage = 0;
  float pHValue = 0;

  // taking 100 samples and adding with 10 milliseconds delay
  for (x = 0; x < 100; x++) {
    phTot += analogRead(phport);
    delay(1);
  }
  float phAvg = phTot / 100;

  phVoltage = phAvg * (3.3 / 4095.0);
  phVoltage -= 0.05;  // Add xxx to phVoltage
  pHValue = (phVoltage + 0.1) * m + C;
  pHValue += 0.55;

  Serial.print("phVoltage =");
  Serial.print(phVoltage);
  Serial.print(" ");
  Serial.print("pH =");
  Serial.println(pHValue);

  delay(1000);
}

void loop() {
  PHsensor();
}
