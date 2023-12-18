#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif

#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

#include "DHT.h"

// #define WIFI_SSID "Innovation 2.4GHz"
// #define WIFI_PASSWORD "Passw0rd@1"
// #define WIFI_SSID "ibomcrmon"
// #define WIFI_PASSWORD "12345678"
#define WIFI_SSID "AsefaIoT"
#define WIFI_PASSWORD "Asf026867766"

#define API_KAY "SfentqzDhmvn6CSXNISeLoalFMXXQTJJg46Y17fU"

#define DATABASE_URL "https://test-esp32-14072-default-rtdb.firebaseio.com/"

/////////////////////////////////////////////////////////////

IPAddress local_IP(172, 16, 110, 129);
// Set your Gateway IP address
IPAddress gateway(172, 16, 110, 254);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);

/////////////////////////////////////////////////////////////

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

#define waterXKC 33
#define re4 25
#define re1 32
#define re2 27
#define re3 14

#define waterHW 15

#define DHTPIN 0
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

int sensorValue = 0;

float a1, b1;
float h, t;

String Humi, Temp;

bool c1, re1state, re2state;
bool re4state = false;

void setup() {
  Serial.begin(115200);

  // pinMode(waterHW, INPUT);
  pinMode(waterXKC, INPUT_PULLDOWN);
  pinMode(re4, OUTPUT);
  pinMode(re1, OUTPUT);
  pinMode(re2, OUTPUT);
  pinMode(re3, OUTPUT);
  digitalWrite(re1, 1);
  digitalWrite(re2, 1);
  digitalWrite(re3, 1);

  delay(1000);

  ////// Configures static IP address//////////////////////////////
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS)) {
    Serial.println("STA Failed to configure");
  }
  /////////////////////////////////////////////////////////////////

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi ;p");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  //print localIP
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  // Serial.println();

  // Print ESP MAC Address
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());

  Serial.printf("FireBase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  config.api_key = API_KAY;
  config.database_url = DATABASE_URL;

  Firebase.begin(DATABASE_URL, API_KAY);
  Firebase.setDoubleDigits(5);

  // Serial.println(F("DHTxx test!"));
  dht.begin();
}

void ReadHumiTemp() {
  // Wait a few seconds between measurements.
  delay(2000);

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

  // // คํานวณดัชนีความร้อนเป็นฟาเรนไฮต์ (ค่าเริ่มต้น)
  // float hif = dht.computeHeatIndex(f, h);
  // คํานวณดัชนีความร้อนเป็นเซลเซียส (isFahreheit = false)
  // float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("% Temperature: "));
  Serial.print(t);
  Serial.println(F(" C "));
}

void WaterLevel() {
  //ควบุมระดับน้ำ เปิดน้ำเมื่อลดต่ำกว่ากำหนด
  if (digitalRead(waterXKC) > 0) {
    digitalWrite(re4, HIGH);
    Serial.println("re4 off");
    re4state = false;

  } else if (digitalRead(waterXKC) == 0) {
    digitalWrite(re4, LOW);
    Serial.println("re4 on");
    re4state = true;
  }
}

void WaterSensor() {
  sensorValue = analogRead(waterHW);
  Serial.printf("WaterSensor --> ");
  Serial.println(sensorValue);

  if (sensorValue > 1000) {
    digitalWrite(re1, LOW);
    Serial.println("re1 on");
    re1state = true;
  } else {
    digitalWrite(re1, HIGH);
    Serial.println("re1 off");
    re1state = false;
  }
}

void loop() {
  WaterSensor();
  delay(50);
  WaterLevel();
  delay(50);
  ReadHumiTemp();
  delay(50);


  if (Firebase.ready()) {
    Firebase.setFloat(fbdo, "/Humidity", h);  //ตอนออกต้องเป็น %
    delay(50);
    Firebase.setFloat(fbdo, "/Temperature", t);
    delay(50);
    Firebase.setBool(fbdo, "/relay1state/re1", re1state);
    delay(50);
    Firebase.setBool(fbdo, "/relay1state/re4", re4state);
    delay(50);


    Serial.printf("Get float Humidity  -->  %s\n", Firebase.getFloat(fbdo, "/Humidity") ? String(fbdo.to<float>()).c_str() : fbdo.errorReason().c_str());
    // a1 = fbdo.to<float>();
    Serial.printf("Get float Temperature -->  %s\n", Firebase.getFloat(fbdo, "/Temperature") ? String(fbdo.to<float>()).c_str() : fbdo.errorReason().c_str());
    // b1 = fbdo.to<float>();
    Serial.printf("Get bool re1 -->  %s\n", Firebase.getBool(fbdo, "relay1state/re1") ? String(fbdo.to<bool>()).c_str() : fbdo.errorReason().c_str());
    // c1 = fbdo.to<bool>();
    Serial.printf("Get bool re4 -->  %s\n", Firebase.getBool(fbdo, "relay1state/re4") ? String(fbdo.to<bool>()).c_str() : fbdo.errorReason().c_str());


    delay(1000);
    Serial.println();
    Serial.println("-------------------------------------");

    delay(1000);
  }
}
