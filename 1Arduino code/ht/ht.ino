void setup() {
  // เริ่มต้นการสื่อสารกับ Serial Monitor ที่ baud rate 115200
  Serial.begin(115200);

  // ปริ้นข้อความแนะนำผู้ใช้ให้ป้อนค่า phvoltage
  // Serial.print("phvoltage = ");
}

void loop() {
  float h = 64.60;
  float t = 30.7;
  // ตรวจสอบว่ามีข้อมูลเข้ามาทาง Serial Monitor หรือไม่
  if (Serial.available() > 0) {
    // อ่านค่าที่ผู้ใช้ป้อนเข้ามา
    float red = Serial.parseFloat();
    if (red != 0.0) {

      // ปริ้นค่า phvoltage และ pH ลงใน Serial Monitor
      Serial.print("Humididity: ");
      Serial.print((h + red));
      Serial.print(" %");

      Serial.print(" Temperature: ");
      Serial.print((t + red));
      Serial.println(" C");
    }
    // ปริ้นข้อความแนะนำผู้ใช้ให้ป้อนค่า phvoltage ใหม่อีกครั้ง
    // Serial.println("phvoltage = ");
  }
}
