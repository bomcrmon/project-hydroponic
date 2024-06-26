void setup() {
  // เริ่มต้นการสื่อสารกับ Serial Monitor ที่ baud rate 115200
  Serial.begin(115200);

  // ปริ้นข้อความแนะนำผู้ใช้ให้ป้อนค่า phvoltage
  Serial.print("phvoltage = ");
}

void loop() {
  // ตรวจสอบว่ามีข้อมูลเข้ามาทาง Serial Monitor หรือไม่
  if (Serial.available() > 0) {
    // อ่านค่าที่ผู้ใช้ป้อนเข้ามา
    float phvoltage = Serial.parseFloat();
    if (phvoltage != 0.0) {
      // คำนวณค่า pH จากค่า phvoltage
      float ph = 4.2424 * phvoltage;

      // ปริ้นค่า phvoltage และ pH ลงใน Serial Monitor
      Serial.print("phvoltage = ");
      Serial.print(phvoltage);
      Serial.print(" ph = ");
      Serial.println(ph);
    }
    // ปริ้นข้อความแนะนำผู้ใช้ให้ป้อนค่า phvoltage ใหม่อีกครั้ง
    // Serial.println("phvoltage = ");
  }
}
