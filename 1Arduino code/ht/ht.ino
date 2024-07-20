#include <Arduino.h>

const int interval = 10000;  // ระยะเวลาในการพิมพ์ข้อความ (10000 มิลลิวินาที = 10 วินาที)
unsigned long previousMillis = 0;
int stateIndex = 0;

// ข้อมูลความชื้นและอุณหภูมิที่ต้องการพิมพ์
float humidity[] = {64.0, 68.0, 59.0, 60.0, 61.0, 69.0};
float temperature[] = {32.8, 33.3, 36.5, 35.0, 34.8, 39.5};

void setup() {
  Serial.begin(115200);  // เริ่มต้นการเชื่อมต่อแบบ serial
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    Serial.print("Humidity: ");
    Serial.print(humidity[stateIndex]);
    Serial.print(" %");

    Serial.print("  Temperature: ");
    Serial.print(temperature[stateIndex]);
    Serial.println(" °C");
    
    stateIndex = (stateIndex + 1) % 6;  // เลื่อนไปยังข้อมูลถัดไป และวนกลับมาที่เริ่มต้นเมื่อถึงสิ้นสุดลำดับ
  }
}
