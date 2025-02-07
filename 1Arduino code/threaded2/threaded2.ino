#include <WiFi.h>
#include <FirebaseESP32.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

#define API_KEY "SfentqzDhmvn6CSXNISeLoalFMXXQTJJg46Y17fU"
#define DATABASE_URL "https://test-esp32-14072-default-rtdb.firebaseio.com/"

#define WIFI_SSID "Four-Faith Inno"
#define WIFI_PASSWORD "Scada@2018"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Define LED pins
#define LED_1 2

#define re7 4
#define re8 5
#define re9 23
#define re10 22

#define re11 32
#define re12 33
int pumStirringp, pumpUP;

int quantitysprinklerfertilizers;
int quantitysprinklerwater;
int quantityFT, quantityMB;

TaskHandle_t re7TaskHandle = NULL;
TaskHandle_t re8TaskHandle = NULL;
TaskHandle_t re9TaskHandle = NULL;
TaskHandle_t re10TaskHandle = NULL;

int re7Finished = 0;
int re8Finished = 0;
int re9Finished = 0;
int re10Finished = 0;

bool allActive1 = false;
bool allActive2 = false;
bool allActive3 = false;
bool allActive4 = false;

void setup() {
  // Serial.begin(115200);

  pinMode(LED_1, OUTPUT);
  pinMode(re7, OUTPUT);
  pinMode(re8, OUTPUT);

  pinMode(re9, OUTPUT);
  pinMode(re10, OUTPUT);

  pinMode(re11, OUTPUT);
  pinMode(re12, OUTPUT);

  digitalWrite(re7, 1);
  digitalWrite(re8, 1);
  digitalWrite(re9, 1);
  digitalWrite(re10, 1);

  digitalWrite(re11, 0);
  digitalWrite(re12, 1);

  // Initialize Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  // Serial.print("Connecting to Wi-Fi ;p");
  while (WiFi.status() != WL_CONNECTED) {
    // Serial.print(".");
    delay(300);
  }
  // Serial.println();
  // Serial.print("Connected with IP: ");
  // Serial.println(WiFi.localIP());

  // Serial.print("MAC address: ");
  // Serial.println(WiFi.macAddress());

  // Serial.printf("FireBase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  Firebase.begin(DATABASE_URL, API_KEY);
  Firebase.setDoubleDigits(5);
}

bool getIntFromFirebase(FirebaseData &fbdo, const char *path, int &variable) {
  if (Firebase.getInt(fbdo, path)) {
    // Serial.printf("Get int %s -->  %d\n", path, fbdo.to<int>());
    variable = fbdo.to<int>();
  } else {
    // Serial.printf("Failed to get int %s. Setting to 0. Error: %s\n", path, fbdo.errorReason().c_str());
    variable = 0;
  }
  delay(1);
  return variable;
}

void setIntToFirebase(FirebaseData &fbdo, const char *path, int value) {
  if (fbdo.httpConnected()) {
    Firebase.setInt(fbdo, path, value);
    delay(1);
  } else {
    // Serial.println("Not connected to Firebase. Skipping setInt operation.");
  }
}

void setIntToFirebase1(FirebaseData &fbdo, const char *path, int value) {
  if (fbdo.httpConnected()) {
    Firebase.setInt(fbdo, path, value);
    delay(1);
  } else {
    // Serial.println("Not connected to Firebase. Skipping setInt operation.");
  }
}

void re7quantity(void *arg) {
  // Serial.println("****re7*****");
  int Setrelay;
  allActive1 = true;
  while (true) {
    if (quantitysprinklerfertilizers != 0) {
      Setrelay = quantitysprinklerfertilizers * 1000;
      digitalWrite(re7, LOW);
      digitalWrite(re11, 1);
      digitalWrite(re12, 0);
      // Serial.println("re7 onnnnnnnnnn");
      vTaskDelay(Setrelay / portTICK_PERIOD_MS);
      digitalWrite(re7, HIGH);
      // Serial.println("re7 off");

      quantitysprinklerfertilizers = 0;
      re7Finished = 1;
      allActive1 = 0;
    }
    vTaskDelay(portMAX_DELAY);  // Wait for new tasks
  }
}

void re8quantity(void *arg) {
  // Serial.println("****re8*****");
  int Setrelay;
  allActive2 = 1;

  while (true) {
    if (quantitysprinklerwater != 0) {
      Setrelay = quantitysprinklerwater * 1000;
      digitalWrite(re8, LOW);
      digitalWrite(re11, 1);
      digitalWrite(re12, 0);
      // Serial.println("re8 onnnnnnnnnn");
      vTaskDelay(Setrelay / portTICK_PERIOD_MS);
      digitalWrite(re8, HIGH);
      // Serial.println("re8 off");

      quantitysprinklerwater = 0;
      re8Finished = 1;
      allActive2 = 0;
    }
    vTaskDelay(portMAX_DELAY);  // Wait for new tasks
  }
}

void re9quantity(void *arg) {
  // Serial.println("****re9*****");
  int Setrelay;
  allActive3 = 1;

  while (true) {
    if (quantityFT != 0) {
      Setrelay = quantityFT * 1000;
      digitalWrite(re9, LOW);
      digitalWrite(re11, 1);
      digitalWrite(re12, 0);
      // Serial.println("re9 onnnnnnnnnn");
      vTaskDelay(Setrelay / portTICK_PERIOD_MS);
      digitalWrite(re9, HIGH);
      // Serial.println("re9 off");

      quantityFT = 0;
      re9Finished = 1;
      allActive3 = 0;
    }
    vTaskDelay(portMAX_DELAY);  // ใช้ portMAX_DELAY เพื่อป้องกันการหน่วงเวลาที่ไม่จำเป็น
  }
}
void re10quantity(void *arg) {
  // Serial.println("****re10*****");
  int Setrelay;
  allActive4 = 1;

  while (true) {
    if (quantityMB != 0) {
      Setrelay = quantityMB * 1000;
      digitalWrite(re10, LOW);
      digitalWrite(re11, 1);
      digitalWrite(re12, 0);
      // Serial.println("re10 onnnnnnnnnn");
      vTaskDelay(Setrelay / portTICK_PERIOD_MS);
      digitalWrite(re10, HIGH);
      // Serial.println("re10 off");

      quantityMB = 0;
      re10Finished = 1;
      allActive4 = 0;
    }
    vTaskDelay(portMAX_DELAY);  // Wait for new tasks
  }
}

void loop() {
  digitalWrite(LED_1, HIGH);
  // Serial.println("led on");
  delay(1000);
  digitalWrite(LED_1, LOW);
  // Serial.println("led off");
  delay(1000);

  if (Firebase.ready()) {

    getIntFromFirebase(fbdo, "/quantitysprinklerfertilizers", quantitysprinklerfertilizers);
    if (quantitysprinklerfertilizers != 0 && re7TaskHandle == NULL) {
      xTaskCreate(re7quantity, "re7quantity", 1024, NULL, 1, &re7TaskHandle);
    } else if (quantitysprinklerfertilizers == 0 && re7TaskHandle != NULL) {
      vTaskDelete(re7TaskHandle);
      re7TaskHandle = NULL;
    }
    if (re7Finished) {
      setIntToFirebase(fbdo, "/quantitysprinklerfertilizers", 0);
      re7Finished = 0;
    }

    getIntFromFirebase(fbdo, "/quantitysprinklerwater", quantitysprinklerwater);
    if (quantitysprinklerwater != 0 && re8TaskHandle == NULL) {
      xTaskCreate(re8quantity, "re8quantity", 1024, NULL, 1, &re8TaskHandle);
    } else if (quantitysprinklerwater == 0 && re8TaskHandle != NULL) {
      vTaskDelete(re8TaskHandle);
      re8TaskHandle = NULL;
    }
    if (re8Finished) {
      setIntToFirebase(fbdo, "/quantitysprinklerwater", 0);
      re8Finished = 0;
    }

    getIntFromFirebase(fbdo, "/quantityFT", quantityFT);
    if (quantityFT != 0 && re9TaskHandle == NULL) {
      xTaskCreate(re9quantity, "re9quantity", 1024, NULL, 1, &re9TaskHandle);
    } else if (quantityFT == 0 && re9TaskHandle != NULL) {
      vTaskDelete(re9TaskHandle);
      re9TaskHandle = NULL;
      // Serial.println("------re9delete-------");
    }
    // Check if re9quantity has finished
    if (re9Finished) {
      setIntToFirebase(fbdo, "/quantityFT", 0);
      re9Finished = 0;
    }

    getIntFromFirebase(fbdo, "/quantityMB", quantityMB);
    if (quantityMB != 0 && re10TaskHandle == NULL) {
      xTaskCreate(re10quantity, "re10quantity", 1024, NULL, 1, &re10TaskHandle);
    } else if (quantityMB == 0 && re10TaskHandle != NULL) {
      vTaskDelete(re10TaskHandle);
      re10TaskHandle = NULL;
      // Serial.println("------re10delete-------");
    }

    // Check if re10quantity has finished
    if (re10Finished) {
      setIntToFirebase(fbdo, "/quantityMB", 0);  // Set MBquantity to 0 in Firebase
      re10Finished = 0;
    }

    if (!allActive1 && !allActive2 && !allActive3 && !allActive4) {
      digitalWrite(re11, 0);
      digitalWrite(re12, 1);
    }
  }

  delay(1000);
}
