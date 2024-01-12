#include "DHT.h"

#define waterHW 35
#define waterXKC 33
#define phport 4

#define DHTPIN 25
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

//--------phsensor------------
long phTot;
float pHValue, phAvg, phVoltage;
float C = 0;       //Constant of straight line (Y = mx + C)
float m = 4.2424;  // Slope of straight line (Y = mx + C)
//----------------------------
//------fertilizerSensor------
int sensorValue;
//----------------------------
//------TempHumiSensor------
float h, t;
String Humi, Temp;
//----------------------------
bool waterstate, fertilizersstate;

bool sendFlag = false;  // Control signal to indicate when to send data

void setup() {
  pinMode(phport, INPUT);
  pinMode(waterHW, INPUT);
  pinMode(waterXKC, INPUT_PULLDOWN);

  delay(1000);

  dht.begin();

  Serial2.begin(115200);
  Serial.begin(115200);
  analogReadResolution(12);
}

void PHsensor() {
  phTot = 0;
  phAvg = 0;
  phVoltage = 0;
  pHValue = 0;
  // taking 100 sample and adding with 10 milli second delay
  for (int x = 0; x < 100; x++) {
    phTot += analogRead(phport);
    delay(1);
  }
  phAvg = phTot / 100;

  phVoltage = phAvg * (3.3 / 4095.0);
  phVoltage += 0;  // Add 0.1 to phVoltage
  pHValue = phVoltage * m + C;
  pHValue += 0.5;

  Serial.print("phVoltage = ");
  Serial.print(phVoltage);
  Serial.print(" ");
  Serial.print("pH=");
  Serial.println(pHValue);

}

void ReadHumiTemp() {
  // Wait a few seconds between measurements.
  // delay(1000);

  // อ่านค่าความชื้น
  h = dht.readHumidity();
  // อ่านอุณหภูมิเป็นเซลเซียส (ค่าเริ่มต้น)
  t = dht.readTemperature();
  // // อ่านอุณหภูมิเป็นฟาเรนไฮต์ (isFahrenheit = true)
  // float f = dht.readTemperature(true);

  // ตรวจสอบว่าการอ่านล้มเหลวและออกก่อนกําหนดหรือไม่ (เพื่อลองอีกครั้ง)
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Serial.print(F("Humidity: "));
  // Serial.print(h);
  // Serial.print(F("% Temperature: "));
  // Serial.print(t);
  // Serial.println(F(" C "));
}

void WaterLevel() {
  //ควบุมระดับน้ำ เปิดน้ำเมื่อลดต่ำกว่ากำหนด
  if (digitalRead(waterXKC) > 0) {
    waterstate = true;

  } else if (digitalRead(waterXKC) == 0) {
    waterstate = false;
  }
}

void fertilizerSensor() {
  sensorValue = analogRead(waterHW);
  delay(50);
  float waterLevel = map(sensorValue, 0, 3500, 0, 100);
  if (waterLevel > 35) {
    fertilizersstate = true;
  } else {
    fertilizersstate = false;
  }
}

void serialEvent() {
  while (Serial2.available()) {
    char inChar = (char)Serial2.read();
    if (inChar == 'T') {
      sendFlag = true;  // ตั้งค่าสัญญาณควบคุมเพื่อส่งข้อมูลจาก TX
    }
  }
  // ลบข้อมูลที่อ่านมาทั้งหมด
  Serial2.flush();
}

void loop() {
  /////อ่านค่าเซนเซอร์///////////////
  fertilizerSensor();
  delay(50);

  WaterLevel();
  delay(50);

  ReadHumiTemp();
  delay(50);

  PHsensor();
  delay(50);
  //////////////////////////////////

  ///////////ส่งค่าเซนเซอร์/////////////
  serialEvent();  ////เซ็คว่าฝั่งนู้นต้องการรับข้อมูลหรือไม่
  if (sendFlag) {
    String data = "";
    data += fertilizersstate ? "1" : "0";
    data += "|";
    data += waterstate ? "1" : "0";
    data += "|";
    data += h;
    data += "|";
    data += t;
    data += "|";
    data += pHValue;

    Serial.println(data);
    Serial2.println(data);

    sendFlag = false;
  }
  ////////////////////////////
}
