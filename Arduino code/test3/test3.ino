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
#define waterHW 32
#define waterXKC 33

#define re1 19
#define re2 18
#define re3 5
#define re4 17
#define re5 16
#define re6 4
#define re7 14
#define re8 13


#define DHTPIN 25
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

int sensorValue;

float a1, b1;
float h, t;

String Humi, Temp;

bool fan, led, sprinkler, valve, re1state, re2state, re3state, re4state;
bool Autosystem, waterstate, fertilizersstate, pumpwater, pumpfertilizers;

void setup() {
  Serial.begin(115200);

  // pinMode(waterHW, INPUT);
  pinMode(waterXKC, INPUT_PULLDOWN);

  pinMode(re1, OUTPUT);
  pinMode(re2, OUTPUT);
  pinMode(re3, OUTPUT);
  pinMode(re4, OUTPUT);

  pinMode(re5, OUTPUT);
  pinMode(re6, OUTPUT);
  pinMode(re7, OUTPUT);
  pinMode(re8, OUTPUT);

  digitalWrite(re1, 1);
  digitalWrite(re2, 1);
  digitalWrite(re3, 1);
  digitalWrite(re4, 1);
  digitalWrite(re5, 1);
  digitalWrite(re6, 1);
  digitalWrite(re7, 1);
  digitalWrite(re8, 1);

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
  Serial.begin(115200);
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

void NFRE(bool state, int relay) {
  // Serial.printf("Get bool relaystate -->  %s\n", Firebase.getBool(fbdo, "/relaystate/" + String(state)) ? String(fbdo.to<bool>()).c_str() : fbdo.errorReason().c_str());
  // state = fbdo.to<bool>();
  // state = Firebase.getBool(fbdo, "/relaystate/" + String(state)) ? fbdo.to<bool>();
  if (state == true) {
    digitalWrite(relay, LOW);
    Serial.println("pin " + String(relay) + " on");
  } else {
    digitalWrite(relay, HIGH);
    Serial.println("pin " + String(relay) + " off");
  }
}

void WaterLevel() {
  //ควบุมระดับน้ำ เปิดน้ำเมื่อลดต่ำกว่ากำหนด
  if (digitalRead(waterXKC) > 0) {
    // digitalWrite(re4, HIGH);
    // Serial.println("re4 off");
    waterstate = true;

  } else if (digitalRead(waterXKC) == 0) {
    // digitalWrite(re4, LOW);
    // Serial.println("re4 on");
    waterstate = false;
  }
}
void fertilizerSensor() {
  sensorValue = analogRead(waterHW);
  delay(50);
  float waterLevel = map(sensorValue, 0, 3500, 0, 100);
  // Serial.printf("WaterLevel --> ");
  // Serial.print(String(waterLevel));
  // Serial.println("%");
  delay(50);
  if (waterLevel > 15) {
    // digitalWrite(re1, LOW);
    // Serial.println("re1 on");
    fertilizersstate = true;
  } else {
    // digitalWrite(re1, HIGH);
    // Serial.println("re1 off");
    fertilizersstate = false;
  }
}
void SetLed() {
  if (led == true) {
    digitalWrite(re3, LOW);
    Serial.println("re3 on");
  } else {
    digitalWrite(re3, HIGH);
    Serial.println("re3 off");
  }
}
void SetFan() {
  if (fan == true) {
    digitalWrite(re5, LOW);
    Serial.println("re5 on");
  } else {
    digitalWrite(re5, HIGH);
    Serial.println("re5 off");
  }
}
void SetValve() {
  if (valve == true) {
    digitalWrite(re2, LOW);
    Serial.println("re2 on");
  } else {
    digitalWrite(re2, HIGH);
    Serial.println("re2 off");
  }
}
void SetSprinkler() {
  if (sprinkler == true) {
    digitalWrite(re6, LOW);
    Serial.println("re6 on");
  } else {
    digitalWrite(re6, HIGH);
    Serial.println("re6 off");
  }
}

void loop() {
  // Serial.printf("Get bool Autosystem -->  %s\n", Firebase.getBool(fbdo, "/Autosystem") ? String(fbdo.to<bool>()).c_str() : fbdo.errorReason().c_str());
  Autosystem = Firebase.getBool(fbdo, "/Autosystem");
  Autosystem = fbdo.to<bool>();
  if (Autosystem == true) {
    fertilizerSensor();
    delay(50);
    // NFRE(fertilizersstate, re1);
    // delay(50);
    WaterLevel();
    delay(50);
    // NFRE(waterstate, re4);
    // delay(50);
    ReadHumiTemp();
    delay(50);

    if (Firebase.ready()) {

      Firebase.setFloat(fbdo, "/Humidity", h);  //ตอนออกต้องเป็น %
      delay(50);
      Firebase.setFloat(fbdo, "/Temperature", t);
      delay(50);
      Firebase.setBool(fbdo, "/fertilizersstate", fertilizersstate);
      delay(50);
      Firebase.setBool(fbdo, "/waterstate", waterstate);
      delay(50);



      Serial.printf("Get float Humidity  -->  %s\n", Firebase.getFloat(fbdo, "/Humidity") ? String(fbdo.to<float>()).c_str() : fbdo.errorReason().c_str());
      // a1 = fbdo.to<float>();
      delay(50);

      Serial.printf("Get float Temperature -->  %s\n", Firebase.getFloat(fbdo, "/Temperature") ? String(fbdo.to<float>()).c_str() : fbdo.errorReason().c_str());
      // b1 = fbdo.to<float>();
      delay(50);

      Serial.printf("Get bool fertilizersstate -->  %s\n", Firebase.getBool(fbdo, "/fertilizersstate") ? String(fbdo.to<bool>()).c_str() : fbdo.errorReason().c_str());
      delay(50);

      Serial.printf("Get bool waterstate -->  %s\n", Firebase.getBool(fbdo, "/waterstate") ? String(fbdo.to<bool>()).c_str() : fbdo.errorReason().c_str());
      delay(50);

      Serial.println();
      Serial.println("**************************");
      Serial.println();

      Serial.printf("Get bool pumpfertilizers -->  %s\n", Firebase.getBool(fbdo, "/relaystate/pumpfertilizers") ? String(fbdo.to<bool>()).c_str() : fbdo.errorReason().c_str());
      pumpfertilizers = fbdo.to<bool>();
      // NFRE(fertilizersstate, re1);
      // delay(50);
      delay(50);

      Serial.printf("Get bool valve -->  %s\n", Firebase.getBool(fbdo, "/relaystate/valve") ? String(fbdo.to<bool>()).c_str() : fbdo.errorReason().c_str());
      valve = fbdo.to<bool>();
      delay(50);

      Serial.printf("Get bool led -->  %s\n", Firebase.getBool(fbdo, "/relaystate/led") ? String(fbdo.to<bool>()).c_str() : fbdo.errorReason().c_str());
      led = fbdo.to<bool>();
      delay(50);

      Serial.printf("Get bool pumpwater -->  %s\n", Firebase.getBool(fbdo, "/relaystate/pumpwater") ? String(fbdo.to<bool>()).c_str() : fbdo.errorReason().c_str());
      pumpwater = fbdo.to<bool>();
      // NFRE(waterstate, re4);
      // delay(50);
      delay(50);

      Serial.printf("Get bool fan -->  %s\n", Firebase.getBool(fbdo, "/relaystate/fan") ? String(fbdo.to<bool>()).c_str() : fbdo.errorReason().c_str());
      fan = fbdo.to<bool>();
      delay(50);

      Serial.printf("Get bool sprinkler -->  %s\n", Firebase.getBool(fbdo, "/relaystate/sprinkler") ? String(fbdo.to<bool>()).c_str() : fbdo.errorReason().c_str());
      sprinkler = fbdo.to<bool>();
      delay(50);

      NFRE(pumpfertilizers, re1);
      delay(50);

      SetValve();
      delay(50);

      SetLed();
      delay(50);

      NFRE(pumpwater, re4);
      delay(50);

      SetFan();
      delay(50);
      
      SetSprinkler();
      delay(50);

      delay(1000);
      Serial.println("----------------------------------------------------");
      Serial.println();
      delay(1000);
    }
  } else if (Autosystem == false) {
    Serial.println("manual mode");
    delay(1000);
  }
}
