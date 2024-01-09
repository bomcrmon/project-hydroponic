#include "DFRobot_PH.h"
#include <Arduino.h>

#define PH_PIN 32  // แทนที่ด้วยหมายเลขขาที่คุณใช้กับเซนเซอร์ pH บน ESP32
float voltage, phValue, temperature = 25;
DFRobot_PH ph;

void setup()
{
  Serial.begin(115200);
  ph.begin();
}

void loop()
{
  static unsigned long timepoint = millis();
  if (millis() - timepoint > 1000U) // ช่วงเวลา: 1 วินาที
  {
    timepoint = millis();
    int adcValue = analogRead(PH_PIN); // อ่านค่าแรงดัน
    voltage = adcValue / 4095.0 * 5000; // แปลงค่า ADC เป็นแรงดัน
    //temperature = readTemperature(); // อ่านค่าอุณหภูมิจากเซนเซอร์ของคุณเพื่อดำเนินการปรับอุณหภูมิ
    phValue = ph.readPH(voltage, temperature); // แปลงแรงดันเป็น pH พร้อมการปรับอุณหภูมิ
    Serial.print("temperature:");
    Serial.print(temperature, 1);
    Serial.print("^C pH:");
    Serial.println(phValue, 2);
  }
  ph.calibration(voltage, temperature); // กระบวนการสอนด้วย Serial CMD
}

float readTemperature()
{
  // เพิ่มโค้ดของคุณที่นี่เพื่อดึงข้อมูลอุณหภูมิจากเซนเซอร์ของคุณ
}
