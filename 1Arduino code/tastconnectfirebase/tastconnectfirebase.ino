#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif

//Provide the token generation process info.
#include <addons/TokenHelper.h>

//Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "bomcrmon"
#define WIFI_PASSWORD "bom0885789765"

//For the following credentials, see examples/Authentications/SignInAsUser/EmailPassword/EmailPassword.ino

/* 2. Define the API Key */
#define API_KEY "EjMPVLNSVkJjQmZG2DItJYEAdgZZonUBomUt3d8p"

/* 3. Define the RTDB URL */
#define DATABASE_URL "https://test-1368b-default-rtdb.asia-southeast1.firebasedatabase.app/"  //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app


//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;


// String main="";
#define led1 33
#define led2 25
int a, b, c, x, y, z;


void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.begin(115200);
  delay(2000);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  config.database_url = DATABASE_URL;



  //////////////////////////////////////////////////////////////////////////////////////////////
  //Please make sure the device free Heap is not lower than 80 k for ESP32 and 10 k for ESP8266,
  //otherwise the SSL connection will fail.
  //////////////////////////////////////////////////////////////////////////////////////////////

  Firebase.begin(DATABASE_URL, API_KEY);

  //Comment or pass false value when WiFi reconnection will control by your code or third party library
  // Firebase.reconnectWiFi(true);

  Firebase.setDoubleDigits(5);
}

void loop() {


  x = random(10, 100);
  y = random(101, 200);
  z = random(0, 9);

  if (Firebase.ready()) {

    //Firebase.setInt(fbdo, main, 5);
    Firebase.setInt(fbdo, "/test/a", x);
    Firebase.setInt(fbdo, "/test/b", y);
    Firebase.setInt(fbdo, "/test/c", z);


    Serial.printf("Get int a--  %s\n", Firebase.getInt(fbdo, "/test/a") ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
    a = fbdo.to<int>();
    Serial.printf("Get int b--  %s\n", Firebase.getInt(fbdo, "/test/b") ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
    b = fbdo.to<int>();
    Serial.printf("Get int c--  %s\n", Firebase.getInt(fbdo, "/test/c") ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
    c = fbdo.to<int>();
    digitalWrite(led1, 1);
    delay(1000);
    digitalWrite(led1, 0);
    delay(2500);
    Serial.println();
    Serial.print("  a: ");
    Serial.print(a);
    Serial.print("  b: ");
    Serial.print(b);
    Serial.print("  c: ");
    Serial.print(c);

    Serial.println();
    Serial.println("-------------------------------------");
    Serial.println();
    digitalWrite(led2, 1);
    delay(2500);
    digitalWrite(led2, 0);


    delay(2500);
  }
}