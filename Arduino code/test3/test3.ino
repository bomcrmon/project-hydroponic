#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif

#include <addons/TokenHelper.h>

#include <addons/RTDBHelper.h>

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

#define water 33
#define pump 25
#define re1 32
#define re2 27
#define re3 14

int a1, a2, b1, b2, c1, c2;
int x1, x2, y3, y2, z1, z2;
int a3, b3, c3;

void setup() {
  Serial.begin(115200);

  pinMode(water, INPUT_PULLDOWN);
  pinMode(pump, OUTPUT);
  pinMode(re1, OUTPUT);
  pinMode(re2, OUTPUT);
  pinMode(re3, OUTPUT);
  digitalWrite(re1, 1);
  digitalWrite(re2, 1);
  digitalWrite(re3, 1);

  delay(2000);

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
}

void WaterLevel() {
  //ควบุมระดับน้ำ เปิดน้ำเมื่อลดต่ำกว่ากำหนด
  if (digitalRead(water) > 0) {
    digitalWrite(pump, HIGH);
    Serial.println("pump off");

  } else if (digitalRead(water) == 0) {
    digitalWrite(pump, LOW);
    Serial.println("pump on");
  }
}

void loop() {
  x1 = random(0, 2);
  y3 = random(11, 13);
  z1 = random(21, 23);
  x2 = random(31, 33);
  y2 = random(41, 43);
  z2 = random(51, 53);

  WaterLevel();

  if (Firebase.ready()) {

    Firebase.setInt(fbdo, "/test/a", x1);
    Firebase.setInt(fbdo, "/test/b", y3);
    Firebase.setInt(fbdo, "/test/c", z1);

    Firebase.setInt(fbdo, "/test2/a", x2);
    Firebase.setInt(fbdo, "/test2/b", y2);
    Firebase.setInt(fbdo, "/test2/c", z2);

    Serial.printf("Get int a1 -->  %s\n", Firebase.getInt(fbdo, "/test/a") ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
    a1 = fbdo.to<int>();
    Serial.printf("Get int b1 -->  %s\n", Firebase.getInt(fbdo, "/test/b") ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
    b1 = fbdo.to<int>();
    Serial.printf("Get int c1 -->  %s\n", Firebase.getInt(fbdo, "/test/c") ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
    c1 = fbdo.to<int>();

    Serial.println();

    Serial.printf("Get int a2 -->  %s\n", Firebase.getInt(fbdo, "/test2/a") ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
    a2 = fbdo.to<int>();
    Serial.printf("Get int b2 -->  %s\n", Firebase.getInt(fbdo, "/test2/b") ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
    b2 = fbdo.to<int>();
    Serial.printf("Get int c2 -->  %s\n", Firebase.getInt(fbdo, "/test2/c") ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
    c2 = fbdo.to<int>();
    delay(1000);

    a3 = a1 + a2;
    b3 = b1 * b2;
    c3 = c2 - c1;

    Serial.println();

    if (a1 == 0) {
      digitalWrite(re1, 0);
      Serial.println("LED1 ON");
      delay(500);
    }
    if (b1 == 11) {
      digitalWrite(re2, 0);
      Serial.println("LED2 ON");
      delay(500);
    }
    if (c1 == 21) {
      digitalWrite(re3, 0);
      Serial.println("LED3 ON");
      delay(500);
    }
    if (a1 == 1) {
      digitalWrite(re1, 1);
      Serial.println("LED1 OFF");
      delay(500);
    }
    if (b1 == 12) {
      digitalWrite(re2, 1);
      Serial.println("LED2 OFF");
      delay(500);
    }
    if (c1 == 22) {
      digitalWrite(re3, 1);
      Serial.println("LED3 OFF");
      delay(500);
    }

    Serial.println();
    Serial.print("a1 + a2 = ");
    Serial.println(a3);
    Serial.print("b1 * b2 = ");
    Serial.println(b3);
    Serial.print("c2 - c1 = ");
    Serial.println(c3);

    delay(1000);
    Firebase.setInt(fbdo, "/test3/a", a3);
    Firebase.setInt(fbdo, "/test3/b", b3);
    Firebase.setInt(fbdo, "/test3/c", c3);

    // Serial.println();
    Serial.println("-------------------------------------");
    Serial.println();
    delay(10000);
  }
}
