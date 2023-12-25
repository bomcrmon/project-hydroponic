#include <WiFi.h>
#include <FirebaseESP32.h>
#include "time.h"
#include "sntp.h"

#define WIFI_SSID "AsefaIoT"
#define WIFI_PASSWORD "Asf026867766"

#define FIREBASE_HOST "https://peppy-myth-374604-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "QDoJ4UjdgQiBdnjFVKlXFOli9ctNYQB3zCsrBpUa"

IPAddress local_IP(172, 16, 110, 129);
IPAddress gateway(172, 16, 110, 254);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);

FirebaseData firebaseData;

const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";
const long gmtOffset_sec = 7 * 3600;
const int daylightOffset_sec = 0;

const char* time_zone = "Asia/Bangkok";
String bomtime;
float x;

void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("No time available (yet)");
    return;
  }
  bomtime = tmToString(&timeinfo);

  // Print the time
  Serial.println(bomtime);
}
String tmToString(struct tm* timeinfo) {
  char buffer[50];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
  return String(buffer);
}
void timeavailable(struct timeval* t) {
  Serial.println("Got time adjustment from NTP!");
  printLocalTime();
}

void setup() {
  Serial.begin(115200);

  sntp_set_time_sync_notification_cb(timeavailable);

  sntp_servermode_dhcp(1);

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);

  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS)) {
    Serial.println("STA Failed to configure");
  }

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  // ส่งข้อมูลไปยัง Firebase
  sendDataToFirebase();

  // รอ 5 นาที
  delay(30000);
}

void sendDataToFirebase() {
  // รับ timestamp
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("No time available (yet)");
    return;
  }
  char timestamp[20];
  strftime(timestamp, sizeof(timestamp), "%d-%m-%Y %H:%M:%S", &timeinfo);
  Serial.println("Sending timestamp to Firebase: " + String(timestamp));

  // รับค่าอื่น ๆ (เป็นตัวอย่างเช่นค่าอุณหภูมิ)
  float temperatureValue = readTemperature();

  // สร้าง JSON object
  FirebaseJson json;
  json.add("timestamp", timestamp);
  json.add("temperature", temperatureValue);

  // ส่งข้อมูลไปยัง Firebase โดยใช้ push
  Firebase.push(firebaseData, "/data", json);

  // if (firebaseData.dataAvailable()) {
  //   Serial.println("Data sent to Firebase");
  // } else {
  //   Serial.println("Error sending data to Firebase");
  // }
}

float readTemperature() {
  x = random(0, 40);
  // ในฟังก์ชันนี้คุณควรดึงค่าอุณหภูมิจากเซ็นเซอร์หรือแหล่งข้อมูลที่เหมาะสม
  // สำหรับตัวอย่างนี้ให้ใส่ค่าอุณหภูมิจำลองเพื่อเป็นตัวอย่าง
  return x;
}
