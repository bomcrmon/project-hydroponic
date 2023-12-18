#include "DHT.h"
#define DHTPIN 0
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Serial.println(F("DHTxx test!"));

  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // อ่านค่าความชื้น
  float h = dht.readHumidity();
  // อ่านอุณหภูมิเป็นเซลเซียส (ค่าเริ่มต้น)
  float t = dht.readTemperature();
  // อ่านอุณหภูมิเป็นฟาเรนไฮต์ (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // ตรวจสอบว่าการอ่านล้มเหลวและออกก่อนกําหนดหรือไม่ (เพื่อลองอีกครั้ง)
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // คํานวณดัชนีความร้อนเป็นฟาเรนไฮต์ (ค่าเริ่มต้น)
  float hif = dht.computeHeatIndex(f, h);
  // คํานวณดัชนีความร้อนเป็นเซลเซียส (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("% Temperature: "));
  Serial.print(t);
  Serial.println(F(" C "));
  // Serial.print(f);
  // Serial.print(F(" F Heat index: "));
  // Serial.print(F(" Heat index: "));
  // Serial.print(hic);
  // Serial.println(F(" C "));
  // Serial.print(hif);
  // Serial.println(F(" F"));
}
