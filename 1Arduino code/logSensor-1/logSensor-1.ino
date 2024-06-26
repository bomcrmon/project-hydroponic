#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <FirebaseESP32.h>
#include <TimeLib.h>

// ใส่ข้อมูลเครือข่าย WiFi ของคุณ
const char* ssid = "bomcrmon";
const char* password = "bom0885789765";

// ตั้งค่า Firebase
#define FIREBASE_HOST "https://test-esp32-14072-default-rtdb.firebaseio.com/"  // ตัวอย่าง "your-project-id.firebaseio.com"
#define FIREBASE_AUTH "AIzaSyDC4RoIxtD36gbhFYJeCGEPFXgqDbhk2Cw"

// ตั้งค่าเวลา NTP เซิร์ฟเวอร์
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 25200, 60000);  // 25200 วินาที เท่ากับ GMT+7

// ตัวแปรที่เก็บเวลาปัจจุบัน
String timeset;

// ตัวแปรสำหรับเก็บค่าความชื้น อุณหภูมิ และค่า pH
float humidity = 50.0;     // ตัวอย่างค่าความชื้น
float temperature = 25.0;  // ตัวอย่างค่าอุณหภูมิ
float ph = 7.0;            // ตัวอย่างค่าพีเอช

FirebaseData firebaseData;

unsigned long previousMillis = 0;
const long interval = 3600000;  // 1 ชั่วโมง (3600000 มิลลิวินาที)

void setup() {
  Serial.begin(115200);

  // เริ่มการเชื่อมต่อ WiFi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  // เริ่ม NTPClient
  timeClient.begin();

  // เริ่มการเชื่อมต่อ Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop() {
  timeClient.update();

  // รับค่าเวลาแบบ epoch
  unsigned long epochTime = timeClient.getEpochTime();

  // ตั้งค่าเวลาในไลบรารี TimeLib
  setTime(epochTime);

  // จัดรูปแบบวันที่และเวลาเป็นสตริง
  timeset = String(year()) + "-" + String(month()) + "-" + String(day()) + " " + String(hour()) + ":" + String(minute()) + ":" + String(second());

  // ตรวจสอบเวลาปัจจุบัน
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    humidity = random(60, 66);        // ตัวอย่างค่าความชื้น
    temperature = random(27, 30);     // ตัวอย่างค่าอุณหภูมิ
    ph = random(6500, 6800) / 100.0;  // ตัวอย่างค่า pH

    // สร้าง JSON object
    FirebaseJson json;
    json.set("timestamp", timeset);
    json.set("humidity", humidity);
    json.set("temperature", temperature);
    json.set("ph", ph);

    // ส่งข้อมูลไปยัง Firebase
    if (Firebase.pushJSON(firebaseData, "/logSensor", json)) {
      Serial.println("Data sent to Firebase successfully");
    } else {
      Serial.println("Failed to send data to Firebase");
      Serial.println(firebaseData.errorReason());
    }

    // แสดงผลข้อมูล
    Serial.print("Current Date and Time: ");
    Serial.println(timeset);
    Serial.print("Humidity: ");
    Serial.println(humidity);
    Serial.print("Temperature: ");
    Serial.println(temperature);
    Serial.print("pH: ");
    Serial.println(ph);
  }

  // ตรวจสอบค่าที่ได้รับจากคีย์บอร์ด
  if (Serial.available() > 0) {
    char input = Serial.read();
    if (input == '1') {
      simulateDataAndSend();
    }
  }
}

void simulateDataAndSend() {
  // อัปเดตเวลา NTP
  timeClient.update();

  // รับค่าเวลาแบบ epoch
  unsigned long epochTime = timeClient.getEpochTime();

  // ตั้งค่าเวลาในไลบรารี TimeLib
  setTime(epochTime);

  for (int i = 0; i < 24; i++) {
    // จัดรูปแบบวันที่และเวลาเป็นสตริง
    timeset = String(year()) + "-" + String(month()) + "-" + String(day()) + " " + String(hour()) + ":" + String(minute()) + ":" + String(second());

    // ตั้งค่าความชื้น อุณหภูมิ และ pH ตัวอย่าง
    humidity = random(60, 66);        // ตัวอย่างค่าความชื้น
    temperature = random(27, 30);     // ตัวอย่างค่าอุณหภูมิ
    ph = random(6500, 6800) / 100.0;  // ตัวอย่างค่า pH

    // สร้าง JSON object
    FirebaseJson json;
    json.set("timestamp", timeset);
    json.set("humidity", humidity);
    json.set("temperature", temperature);
    json.set("ph", ph);

    // ส่งข้อมูลไปยัง Firebase
    if (Firebase.pushJSON(firebaseData, "/logSensor", json)) {
      Serial.println("Data sent to Firebase successfully");
    } else {
      Serial.println("Failed to send data to Firebase");
      Serial.println(firebaseData.errorReason());
    }

    // แสดงผลข้อมูล
    Serial.print("Current Date and Time: ");
    Serial.println(timeset);
    Serial.print("Humidity: ");
    Serial.println(humidity);
    Serial.print("Temperature: ");
    Serial.println(temperature);
    Serial.print("pH: ");
    Serial.println(ph);

    // เลื่อนเวลาไปข้างหน้า 1 ชั่วโมง
    epochTime += 3600;
    setTime(epochTime);
  }
}
