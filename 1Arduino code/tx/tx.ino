//tx
bool fertilizersstate = false;
bool waterstate = true;
float h = 1.225;
float t = 2.333;
float pHValue = 3.666;

bool sendFlag = false;  // Control signal to indicate when to send data

void setup() {
  Serial2.begin(115200);
  Serial.begin(115200);
}

void loop() {
  serialEvent();
  if (sendFlag) {
    h += 1.2;
    t += 1.3;
    pHValue += 1.4;
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
