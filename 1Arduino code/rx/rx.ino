//rx
bool fertilizersState;
bool waterState;
float h;
float t;
float pHValue;

bool sendRequest = false;

void setup() {
  Serial2.begin(115200);
  Serial.begin(115200);
}

// เพิ่มฟังก์ชันนี้ไปในโค้ด
int split(String data, char separator, String *output, int outputSize) {
  int count = 0;
  int pos = 0;

  while ((pos = data.indexOf(separator, pos)) != -1) {
    if (count < outputSize) {
      output[count++] = data.substring(0, pos);
    }
    data = data.substring(pos + 1);
    pos = 0;
  }

  // เพิ่มข้อมูลส่วนท้ายของข้อมูลลงในอาร์เรย์ผลลัพธ์
  if (count < outputSize) {
    output[count++] = data;
  }

  return count;
}

void loop() {
  serialEvent();
  // รับข้อมูล
  String data = Serial2.readStringUntil('\n');

  // แยกข้อมูล
  String values[5];                             // ประกาศอาร์เรย์เพื่อเก็บค่าที่แยก
  int numValues = split(data, '|', values, 5);  // ใช้ฟังก์ชันแยกเพื่อเติมอาร์เรย์

  // ตรวจสอบค่าที่รับมา
  if (numValues == 5) {  // ตรวจสอบว่าได้รับค่าทั้งหมดหรือไม่
    fertilizersState = values[0].equals("1");
    waterState = values[1].equals("1");
    h = values[2].toFloat();
    t = values[3].toFloat();
    pHValue = values[4].toFloat();

    // แสดงข้อมูล
    Serial.println("");
    Serial.print("Fertilizers State: ");
    // Serial.println(fertilizersState);
    if (fertilizersState) {
      Serial.println("true");
    } else {
      Serial.println("false");
    }
    Serial.print("Water State: ");
    // Serial.println(waterState);
    if (waterState) {
      Serial.println("true");
    } else {
      Serial.println("false");
    }
    Serial.print("Humidity: ");
    Serial.println(h);
    Serial.print("Temperature: ");
    Serial.println(t);
    Serial.print("pH Value: ");
    Serial.println(pHValue);
    Serial.println("");
    Serial.println("----------------------------------");

    // ลบข้อมูลที่อ่านมาทั้งหมด
    Serial2.flush();
  }
  delay(5000);
}

void serialEvent() {
  Serial2.println("T");
  Serial.println("T");
  // while (Serial.available()) {
  //   char inChar = (char)Serial.read();
  //   if (inChar == 'T') {
  //     Serial2.println("T");
  //     // Serial.println("T");
  //   }
  // }
}