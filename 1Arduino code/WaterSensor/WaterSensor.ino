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
//*****************************************************************************************//
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
//***********************************************************************************************

#define waterSensor A13
#define led 32

#define waterXKC 32
#define re4 25
// #define re1 32
#define re2 27
#define re3 14

#define DHTPIN 0
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);


int sensorValue = 0;
bool re1state, re2state;

void setup() {
  // Serial.begin(115200);
  // delay(1000);
  // ////// Configures static IP address//////////////////////////////
  // if (!WiFi.config(local_IP, gateway, subnet, primaryDNS)) {
  //   Serial.println("STA Failed to configure");
  // }
  // /////////////////////////////////////////////////////////////////

  // WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  // Serial.print("Connecting to Wi-Fi ;p");
  // while (WiFi.status() != WL_CONNECTED) {
  //   Serial.print(".");
  //   delay(300);
  // }
  // //print localIP
  // Serial.println();
  // Serial.print("Connected with IP: ");
  // Serial.println(WiFi.localIP());
  // // Serial.println();

  // // Print ESP MAC Address
  // Serial.print("MAC address: ");
  // Serial.println(WiFi.macAddress());

  Serial.printf("FireBase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  config.api_key = API_KAY;
  config.database_url = DATABASE_URL;

  Firebase.begin(DATABASE_URL, API_KAY);
  Firebase.setDoubleDigits(5);

  pinMode(led, OUTPUT);
  pinMode(re4, OUTPUT);
  // pinMode(re1, OUTPUT);
  pinMode(re2, OUTPUT);
  pinMode(re3, OUTPUT);
  // digitalWrite(re1, 1);
  digitalWrite(re2, 1);
  digitalWrite(re3, 1);

  delay(1000);
  // pinMode(waterSensor, INPUT);
  Serial.begin(115200);
  // Serial.println(F("DHTxx test!"));
  dht.begin();
}
void WaterSensor() {
  sensorValue = analogRead(A13);
  // float waterLevel = map(sensorValue, 0, 3100, 0, 100);
  Serial.println("**************************************");
  Serial.printf("WaterLevel --> ");
  Serial.println(sensorValue);
  // Serial.println("%");
  Serial.println("**************************************");

  if (sensorValue > 100) {
    digitalWrite(led, LOW);
    Serial.println("re1 on");
    re1state = true;
  } else {
    digitalWrite(led, HIGH);
    Serial.println("re1 off");
    re1state = false;
  }
}

void loop() {
  WaterSensor();
  // val = analogRead(waterSensor);
  // Serial.printf("WaterSensor --> ");
  // Serial.println(val);
  // if (val > 1000) {
  //   digitalWrite(led, LOW);
  // } else {
  //   digitalWrite(led, HIGH);
  // }
  delay(1000);
}
