#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

#define API_KAY "SfentqzDhmvn6CSXNISeLoalFMXXQTJJg46Y17fU"
#define DATABASE_URL "https://test-esp32-14072-default-rtdb.firebaseio.com/"

// #define WIFI_SSID "Innovation 2.4GHz"
// #define WIFI_PASSWORD "Passw0rd@1"
// #define WIFI_SSID "ibomcrmon"
// #define WIFI_PASSWORD "12345678"
#define WIFI_SSID "AsefaIoT"
#define WIFI_PASSWORD "Asf026867766"

/////////// Configures static IP address//////////////////////
IPAddress local_IP(172, 16, 110, 129);
// Set your Gateway IP address
IPAddress gateway(172, 16, 110, 254);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);
/////////////////////////////////////////////////////////////

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

#define re1 32
#define re2 33
#define re3 25
#define re4 26
#define re5 27
#define re6 14
#define re7 12
#define re8 13
// #define re9 21
// #define re10 22
// #define re11 23
// #define re12 15

float h;
float t;
float pHValue;
bool fertilizersState;
bool waterState;

bool fan, led, sprinklerwater, valve, re1state, re2state, re3state, re4state;
bool Autosystem, pumpwater, sprinklerfertilizers;
bool pumpphUP, pumpphDown;

void setup() {

  pinMode(re1, OUTPUT);
  pinMode(re2, OUTPUT);
  pinMode(re3, OUTPUT);
  pinMode(re4, OUTPUT);

  pinMode(re5, OUTPUT);
  pinMode(re6, OUTPUT);
  pinMode(re7, OUTPUT);
  pinMode(re8, OUTPUT);

  // pinMode(re9, OUTPUT);
  // pinMode(re10, OUTPUT);
  // pinMode(re11, OUTPUT);
  // pinMode(re12, OUTPUT);

  digitalWrite(re1, 1);
  digitalWrite(re2, 1);
  digitalWrite(re3, 1);
  digitalWrite(re4, 1);
  digitalWrite(re5, 1);
  digitalWrite(re6, 1);
  digitalWrite(re7, 1);
  digitalWrite(re8, 1);
  // digitalWrite(re9, 1);
  // digitalWrite(re10, 1);
  // digitalWrite(re11, 1);
  // digitalWrite(re12, 1);
  delay(100);

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

  Serial2.begin(115200);
  Serial.begin(115200);
  analogReadResolution(12);
}

void NFRE(bool state, int relay) {
  if (state == true) {
    digitalWrite(relay, LOW);
    Serial.println("pin " + String(relay) + " on");
  } else {
    digitalWrite(relay, HIGH);
    Serial.println("pin " + String(relay) + " off");
  }
}

void serialEvent() {
  Serial2.println("T");
  // while (Serial.available()) {
  //   char inChar = (char)Serial.read();
  //   if (inChar == 'T') {
  //     Serial2.println("T");
  //     // Serial.println("T");
  //   }
  // }
}

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
  Autosystem = Firebase.getBool(fbdo, "/Autosystem");
  Autosystem = fbdo.to<bool>();

  if (Autosystem == true) {
    ///////รับค่าจากเซนเซอร์///////////////
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
      if (fertilizersState) {
        Serial.println("true");
      } else {
        Serial.println("false");
      }
      Serial.print("Water State: ");
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

      // ลบข้อมูลที่อ่านมาทั้งหมด กันข้อมูลแถวยาวววว
      Serial2.flush();
    }
    ///////////////////////////////////

    if (Firebase.ready()) {
      Firebase.setFloat(fbdo, "/pHValue", pHValue);
      delay(10);
      Firebase.setFloat(fbdo, "/Humidity", h);  //ตอนออกต้องเป็น %
      delay(10);
      Firebase.setFloat(fbdo, "/Temperature", t);
      delay(10);
      Firebase.setBool(fbdo, "/fertilizersstate", fertilizersState);
      delay(10);
      Firebase.setBool(fbdo, "/waterstate", waterState);
      delay(10);
      ///////////////////////////เอาข้อมูลมาโชว//////////////////////////////////////////////////
      // Serial.printf("Get float pHValue  -->  %s\n", Firebase.getFloat(fbdo, "/pHValue") ? String(fbdo.to<float>()).c_str() : fbdo.errorReason().c_str());
      // delay(10);

      // Serial.printf("Get float Humidity  -->  %s\n", Firebase.getFloat(fbdo, "/Humidity") ? String(fbdo.to<float>()).c_str() : fbdo.errorReason().c_str());
      // // a1 = fbdo.to<float>();
      // delay(10);

      // Serial.printf("Get float Temperature -->  %s\n", Firebase.getFloat(fbdo, "/Temperature") ? String(fbdo.to<float>()).c_str() : fbdo.errorReason().c_str());
      // // b1 = fbdo.to<float>();
      // delay(10);

      // Serial.printf("Get bool fertilizersstate -->  %s\n", Firebase.getBool(fbdo, "/fertilizersstate") ? String(fbdo.to<bool>()).c_str() : fbdo.errorReason().c_str());
      // delay(10);

      // Serial.printf("Get bool waterstate -->  %s\n", Firebase.getBool(fbdo, "/waterstate") ? String(fbdo.to<bool>()).c_str() : fbdo.errorReason().c_str());
      // delay(10);

      // Serial.println();
      // Serial.println("**************************");
      // Serial.println();

      Serial.printf("Get bool sprinklerfertilizers -->  %s\n", Firebase.getBool(fbdo, "/relaystate/sprinklerfertilizers") ? String(fbdo.to<bool>()).c_str() : fbdo.errorReason().c_str());
      sprinklerfertilizers = fbdo.to<bool>();
      delay(10);

      Serial.printf("Get bool valve -->  %s\n", Firebase.getBool(fbdo, "/relaystate/valve") ? String(fbdo.to<bool>()).c_str() : fbdo.errorReason().c_str());
      valve = fbdo.to<bool>();
      delay(10);

      Serial.printf("Get bool led -->  %s\n", Firebase.getBool(fbdo, "/relaystate/led") ? String(fbdo.to<bool>()).c_str() : fbdo.errorReason().c_str());
      led = fbdo.to<bool>();
      delay(10);

      Serial.printf("Get bool pumpwater -->  %s\n", Firebase.getBool(fbdo, "/relaystate/pumpwater") ? String(fbdo.to<bool>()).c_str() : fbdo.errorReason().c_str());
      pumpwater = fbdo.to<bool>();
      delay(10);

      Serial.printf("Get bool fan -->  %s\n", Firebase.getBool(fbdo, "/relaystate/fan") ? String(fbdo.to<bool>()).c_str() : fbdo.errorReason().c_str());
      fan = fbdo.to<bool>();
      delay(10);

      Serial.printf("Get bool sprinklerwater -->  %s\n", Firebase.getBool(fbdo, "/relaystate/sprinklerwater") ? String(fbdo.to<bool>()).c_str() : fbdo.errorReason().c_str());
      sprinklerwater = fbdo.to<bool>();
      delay(10);

      Serial.printf("Get bool pumpphUP -->  %s\n", Firebase.getBool(fbdo, "/relaystate/pumpphUP") ? String(fbdo.to<bool>()).c_str() : fbdo.errorReason().c_str());
      pumpphUP = fbdo.to<bool>();
      delay(10);

      Serial.printf("Get bool pumpphDown -->  %s\n", Firebase.getBool(fbdo, "/relaystate/pumpphDown") ? String(fbdo.to<bool>()).c_str() : fbdo.errorReason().c_str());
      pumpphDown = fbdo.to<bool>();
      delay(10);

      Serial.println();
      Serial.println("+++++++++++++++++++++++++++");
      Serial.println();

      NFRE(sprinklerfertilizers, re1);
      delay(10);

      // SetValve();
      NFRE(valve, re2);
      delay(10);

      // SetLed();
      NFRE(led, re3);
      delay(10);

      NFRE(pumpwater, re4);
      delay(10);

      // SetFan();
      NFRE(fan, re5);
      delay(10);

      // SetSprinkler();
      NFRE(sprinklerwater, re6);
      delay(10);

      NFRE(pumpphUP, re7);
      delay(10);

      NFRE(pumpphDown, re8);
      delay(10);

      Serial.println("----------------------------------------------------");
      Serial.println();
      delay(10);
    }
  } else if (Autosystem == false) {
    Serial.println("manual mode");
    delay(1000);
  }
}
