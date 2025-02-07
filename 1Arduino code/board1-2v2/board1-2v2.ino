#include "DHT.h"

// #define phport 4
// #define waterHW 35
#define waterXKC 33
#define phport 35

#define DHTPIN 25
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#define FTL50 4
#define FTL100 2

#define MBL50 18
#define MBL100 5

bool FTlit50, FTlit100;
bool MBlit50, MBlit100;

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
  // pinMode(waterHW, INPUT);
  pinMode(waterXKC, INPUT_PULLDOWN);

  pinMode(FTL50, INPUT_PULLUP);
  pinMode(FTL100, INPUT_PULLUP);

  pinMode(MBL50, INPUT_PULLUP);
  pinMode(MBL100, INPUT_PULLUP);

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
  phVoltage += 0.12;  // Add 0.1 to phVoltage
  pHValue = phVoltage * m + C;
  pHValue += 0.2;

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
void ReadLevelFT() {
    FTlit50 = digitalRead(FTL50);
    FTlit100 = digitalRead(FTL100);
}

void ReadLevelMB() {
  if (digitalRead(MBL50) > 0) {
    MBlit50 = true;
  } else {
    FTlit50 = false;
  }

  if (digitalRead(MBL100) > 0) {
    MBlit100 = true;
  } else {
    MBlit100 = false;
  }
}

void WaterLevel() {
  //ควบุมระดับน้ำ
  if (digitalRead(waterXKC) > 0) {
    waterstate = true;
  } else if (digitalRead(waterXKC) == 0) {
    waterstate = false;
  }
}

// void fertilizerSensor() {
//   sensorValue = analogRead(waterHW);
//   delay(50);
//   float waterLevel = map(sensorValue, 0, 3500, 0, 100);
//   if (waterLevel > 35) {
//     fertilizersstate = true;
//   } else {
//     fertilizersstate = false;
//   }
// }

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
  // fertilizerSensor();
  // delay(200);

  WaterLevel();
  delay(200);

  ReadHumiTemp();
  delay(200);

  PHsensor();
  delay(200);

  ReadLevelFT();
  delay(100);

  ReadLevelMB();
  delay(100);
  //////////////////////////////////

  ///////////ส่งค่าเซนเซอร์/////////////
  serialEvent();  ////เซ็คว่าฝั่งนู้นต้องการรับข้อมูลหรือไม่
  if (sendFlag) {
    String data = "";
    data += fertilizersstate ? "1" : "0";
    data += "|";
    data += waterstate ? "1" : "0";
    data += "|";
    data += FTlit50 ? "1" : "0";
    data += "|";
    data += FTlit100 ? "1" : "0";
    data += "|";
    data += h;
    data += "|";
    data += t;
    data += "|";
    data += pHValue;
    data += "|";
    data += MBlit50 ? "1" : "0";
    data += "|";
    data += MBlit100 ? "1" : "0";


    Serial.println(data);
    Serial2.println(data);

    sendFlag = false;
  }
  ////////////////////////////
}
