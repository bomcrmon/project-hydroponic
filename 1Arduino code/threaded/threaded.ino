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

#define re1 25
#define re2 26
#define re7 4
#define re8 5


#define re9 23
#define re10 22

#define re11 32
#define re12 33
// int pumpStirring, pumpUP;


int quantitysprinklerfertilizers, quantitysprinklerwater, quantityFT, quantityMB;
int quantityphup, quantityphdown;

TaskHandle_t re1TaskHandle = NULL;
TaskHandle_t re2TaskHandle = NULL;
TaskHandle_t re7TaskHandle = NULL;
TaskHandle_t re8TaskHandle = NULL;
TaskHandle_t re9TaskHandle = NULL;
TaskHandle_t re10TaskHandle = NULL;

bool re1Finished = 0;
bool re2Finished = 0;
bool re7Finished = 0;
bool re8Finished = 0;
bool re9Finished = 0;
bool re10Finished = 0;

bool reActive1 = false;
bool reActive2 = false;
bool reActive7 = false;
bool reActive8 = false;
bool reActive9 = false;
bool reActive10 = false;

void setup() {
  Serial.begin(115200);

  pinMode(LED_1, OUTPUT);

  pinMode(re1, OUTPUT);
  pinMode(re2, OUTPUT);
  pinMode(re7, OUTPUT);
  pinMode(re8, OUTPUT);
  pinMode(re9, OUTPUT);
  pinMode(re10, OUTPUT);
  pinMode(re11, OUTPUT);
  pinMode(re12, OUTPUT);

  digitalWrite(re1, 1);
  digitalWrite(re2, 1);
  digitalWrite(re7, 1);
  digitalWrite(re8, 1);
  digitalWrite(re9, 1);
  digitalWrite(re10, 1);

  digitalWrite(re11, 0);
  digitalWrite(re12, 1);

  // Initialize Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi ;p");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());

  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());

  Serial.printf("FireBase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  Firebase.begin(DATABASE_URL, API_KEY);
  Firebase.setDoubleDigits(5);
}
void re1quantity(void *arg) {
  Serial.println("****re1*****");
  int Setrelay;
  reActive1 = true;
  while (true) {
    if (quantityphup != 0) {
      Setrelay = quantityphup * 1000;
      digitalWrite(re1, LOW);
      digitalWrite(re11, 1);
      digitalWrite(re12, 0);
      Serial.println("re1 onnnnnnnnnn");
      vTaskDelay(Setrelay / portTICK_PERIOD_MS);
      digitalWrite(re1, HIGH);
      Serial.println("re1 offffffffff");

      quantityphup = 0;
      re1Finished = true;
      reActive1 = false;
    }
    vTaskDelay(portMAX_DELAY);
  }
}
void re2quantity(void *arg) {
  Serial.println("****re2*****");
  int Setrelay;
  reActive2 = true;
  while (true) {
    if (quantityphdown != 0) {
      Setrelay = quantityphdown * 1000;
      digitalWrite(re2, LOW);
      digitalWrite(re11, 1);
      digitalWrite(re12, 0);
      Serial.println("re2 onnnnnnnnnn");
      vTaskDelay(Setrelay / portTICK_PERIOD_MS);
      digitalWrite(re2, HIGH);
      Serial.println("re2 offfffff");

      quantityphdown = 0;
      re2Finished = true;
      reActive2 = false;
    }
    vTaskDelay(portMAX_DELAY);
  }
}
void re7quantity(void *arg) {
  Serial.println("****re7*****");
  int Setrelay;
  reActive7 = true;
  while (true) {
    if (quantitysprinklerfertilizers != 0) {
      Setrelay = quantitysprinklerfertilizers * 1000;
      digitalWrite(re7, LOW);
      Serial.println("re7 onnnnnnnnnn");
      vTaskDelay(Setrelay / portTICK_PERIOD_MS);
      digitalWrite(re7, HIGH);
      Serial.println("re7 offffffff");

      quantitysprinklerfertilizers = 0;
      re7Finished = true;
      reActive7 = false;
    }
    vTaskDelay(portMAX_DELAY);  // Wait for new tasks
  }
}
void re8quantity(void *arg) {
  Serial.println("****re8*****");
  int Setrelay;
  reActive8 = true;

  while (true) {
    if (quantitysprinklerwater != 0) {
      Setrelay = quantitysprinklerwater * 1000;
      digitalWrite(re8, LOW);

      Serial.println("re8 onnnnnnnnnn");
      vTaskDelay(Setrelay / portTICK_PERIOD_MS);
      digitalWrite(re8, HIGH);
      Serial.println("re8 offfffffff");

      quantitysprinklerwater = 0;
      re8Finished = true;
      reActive8 = false;
    }
    vTaskDelay(portMAX_DELAY);  // Wait for new tasks
  }
}
void re9quantity(void *arg) {
  Serial.println("****re9*****");
  int Setrelay;
  reActive9 = true;

  while (true) {
    if (quantityFT != 0) {
      Setrelay = quantityFT * 1000;
      digitalWrite(re9, LOW);
      digitalWrite(re11, 1);
      digitalWrite(re12, 0);
      Serial.println("re9 onnnnnnnnnn");
      vTaskDelay(Setrelay / portTICK_PERIOD_MS);
      digitalWrite(re9, HIGH);
      Serial.println("re9 offffffffff");

      quantityFT = 0;
      re9Finished = true;
      reActive9 = false;
    }
    vTaskDelay(portMAX_DELAY);  // ใช้ portMAX_DELAY เพื่อป้องกันการหน่วงเวลาที่ไม่จำเป็น
  }
}
void re10quantity(void *arg) {
  Serial.println("****re10*****");
  int Setrelay;
  reActive10 = true;

  while (true) {
    if (quantityMB != 0) {
      Setrelay = quantityMB * 1000;
      digitalWrite(re10, LOW);
      digitalWrite(re11, 1);
      digitalWrite(re12, 0);
      Serial.println("re10 onnnnnnnnnn");
      vTaskDelay(Setrelay / portTICK_PERIOD_MS);
      digitalWrite(re10, HIGH);
      Serial.println("re10 offfffffff");

      quantityMB = 0;
      re10Finished = true;
      reActive10 = false;
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

    if (Firebase.getInt(fbdo, "/quantitysprinklerfertilizers")) {
      quantitysprinklerfertilizers = fbdo.to<int>();
      if (quantitysprinklerfertilizers != 0 && re7TaskHandle == NULL) {
        xTaskCreatePinnedToCore(re7quantity, "re7quantity", 1024, NULL, 1, &re7TaskHandle, 0);
      } else if (quantitysprinklerfertilizers == 0 && re7TaskHandle != NULL) {
        vTaskDelete(re7TaskHandle);
        re7TaskHandle = NULL;
      }
      if (re7Finished) {
        Firebase.setInt(fbdo, "/quantitysprinklerfertilizers", 0);
        re7Finished = false;
      }
    }

    if (Firebase.getInt(fbdo, "/quantitysprinklerwater")) {
      quantitysprinklerwater = fbdo.to<int>();
      if (quantitysprinklerwater != 0 && re8TaskHandle == NULL) {
        xTaskCreatePinnedToCore(re8quantity, "re8quantity", 1024, NULL, 1, &re8TaskHandle, 0);
      } else if (quantitysprinklerwater == 0 && re8TaskHandle != NULL) {
        vTaskDelete(re8TaskHandle);
        re8TaskHandle = NULL;
      }
      if (re8Finished) {
        Firebase.setInt(fbdo, "/quantitysprinklerwater", 0);
        re8Finished = false;
      }
    }

    if (Firebase.getInt(fbdo, "/quantityFT")) {
      quantityFT = fbdo.to<int>();
      if (quantityFT != 0 && re9TaskHandle == NULL) {
        xTaskCreatePinnedToCore(re9quantity, "re9quantity", 1024, NULL, 1, &re9TaskHandle, 0);
      } else if (quantityFT == 0 && re9TaskHandle != NULL) {
        vTaskDelete(re9TaskHandle);
        re9TaskHandle = NULL;
      }
      if (re9Finished) {
        Firebase.setInt(fbdo, "/quantityFT", 0);
        re9Finished = false;
      }
    }

    if (Firebase.getInt(fbdo, "/quantityMB")) {
      quantityMB = fbdo.to<int>();
      if (quantityMB != 0 && re10TaskHandle == NULL) {
        xTaskCreatePinnedToCore(re10quantity, "re10quantity", 1024, NULL, 1, &re10TaskHandle, 0);
      } else if (quantityMB == 0 && re10TaskHandle != NULL) {
        vTaskDelete(re10TaskHandle);
        re10TaskHandle = NULL;
      }
      if (re10Finished) {
        Firebase.setInt(fbdo, "/quantityMB", 0);
        re10Finished = false;
      }
    }

    if (Firebase.getInt(fbdo, "/quantityphup")) {
      quantityphup = fbdo.to<int>();
      if (quantityphup != 0 && re1TaskHandle == NULL) {
        xTaskCreatePinnedToCore(re1quantity, "re1quantity", 1024, NULL, 1, &re1TaskHandle, 0);
      } else if (quantityphup == 0 && re1TaskHandle != NULL) {
        vTaskDelete(re1TaskHandle);
        re1TaskHandle = NULL;
      }
      if (re1Finished) {
        Firebase.setInt(fbdo, "/quantityphup", 0);
        re1Finished = false;
      }
    }

    if (Firebase.getInt(fbdo, "/quantityphdown")) {
      quantityphdown = fbdo.to<int>();
      if (quantityphdown != 0 && re2TaskHandle == NULL) {
        xTaskCreatePinnedToCore(re2quantity, "re2quantity", 1024, NULL, 1, &re2TaskHandle, 0);
      } else if (quantityphdown == 0 && re2TaskHandle != NULL) {
        vTaskDelete(re2TaskHandle);
        re2TaskHandle = NULL;
      }
      if (re2Finished) {
        Firebase.setInt(fbdo, "/quantityphdown", 0);
        re2Finished = false;
      }
    }

    if (!reActive1 && !reActive2 && !reActive9 && !reActive10) {
      digitalWrite(re11, 0);
      digitalWrite(re12, 1);
    }
  }

  delay(1000);
}
