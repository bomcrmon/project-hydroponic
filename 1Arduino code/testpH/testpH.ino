#include <WiFi.h>  //kkkjjjnnn
#include <FirebaseESP32.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>
#include <WiFiManager.h>

#define API_KEY "AIzaSyDC4RoIxtD36gbhFYJeCGEPFXgqDbhk2Cw"
#define DATABASE_URL "https://test-esp32-14072-default-rtdb.firebaseio.com/"

WiFiManager wm;

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

#define SWrwf 32

#define re1 23  // pumpup
#define re2 15  // pump stirring
#define re3 25  // led
#define re4 26  // fan
#define re5 27  // pump water
#define re6 2   // valve
#define re7 4   // sprinkler FT
#define re8 5   // sprinkler water

#define re9 21   // q FT
#define re10 22  // q MB
#define re11 14  // pump ph up
#define re12 12  // pump ph down

//////////////////////////////////////////////////////////////
float setph = 600;
int quantitysprinklerfertilizers, quantitysprinklerwater;
int quantityphup, quantityphdown, quantityFT, quantityMB;
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
/////////////////////////////////////////////////////////////

float h;
float t;
float pHValue;

bool microbial, fertilizers, pumpStirring, pumpUP;
bool fertilizersState, waterstatehigh, waterstatelow;

bool fan, re1state, re2state, re3state, re4state;
bool Autosystem, pumpwater, sprinklerfertilizers;
bool pumpphUP, pumpphDown, led, sprinklerwater, valve;

void connect() {
  wm.setClass("invert");
  wm.setConfigPortalTimeout(60);  // auto close configportal after n seconds
  if (wm.autoConnect("@hydroponic farm")) {
    Serial.println("");
    Serial.println("Connected already WiFi : ");
    Serial.println("IP Address : ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("failed to connect");
    delay(1000);
    ESP.restart();
  }
}
void setup() {
  Serial.begin(115200);
  pinMode(SWrwf, INPUT_PULLUP);

  // กำหนดค่าขา GPIO 16 เป็นขา RX
  pinMode(16, INPUT);
  // กำหนดค่าขา GPIO 17 เป็นขา TX
  pinMode(17, OUTPUT);

  pinMode(re1, OUTPUT);
  pinMode(re2, OUTPUT);
  pinMode(re3, OUTPUT);
  pinMode(re4, OUTPUT);
  pinMode(re5, OUTPUT);
  pinMode(re6, OUTPUT);
  pinMode(re7, OUTPUT);
  pinMode(re8, OUTPUT);
  pinMode(re9, OUTPUT);
  pinMode(re10, OUTPUT);
  pinMode(re11, OUTPUT);
  pinMode(re12, OUTPUT);

  digitalWrite(re1, 1);
  digitalWrite(re2, 1);
  digitalWrite(re3, 1);
  digitalWrite(re4, 1);
  digitalWrite(re5, 1);
  digitalWrite(re6, 1);
  digitalWrite(re7, 1);
  digitalWrite(re8, 1);
  digitalWrite(re9, 1);
  digitalWrite(re10, 1);
  digitalWrite(re11, 0);
  digitalWrite(re12, 1);
  delay(10);

  connect();
  // ////// Configures static IP address//////////////////////////////
  // if (!WiFi.config(local_IP, gateway, subnet, primaryDNS)) {
  //   Serial.println("STA Failed to configure");
  // }
  // /////////////////////////////////////////////////////////////////

  // WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  // Serial.print("Connecting to Wi-Fi ;p");
  // while (WiFi.status() != WL_CONNECTED) {
  //   Serial.print(".");
  //   delay(100);
  // }
  //print localIP
  // Serial.println();
  // Serial.print("Connected with IP: ");
  // Serial.println(WiFi.localIP());
  // Serial.println();

  // Print ESP MAC Address
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());

  Serial.printf("FireBase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  Firebase.begin(DATABASE_URL, API_KEY);
  Firebase.setDoubleDigits(5);

  Serial2.begin(115200);
  delay(1000);
}
void Wifi_Reset() {
  if (digitalRead(SWrwf) == LOW) {
    Serial.println("Wifi Reset? watting 2S..");
    delay(2000);
    if (digitalRead(SWrwf) == LOW) {
      delay(10);
      Serial.println("wifi Reset Setting ..OK");
      wm.resetSettings();
      ESP.restart();
    }
  }
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
      // Serial.print("setph = ");
      // Serial.println(setph);
      setph = setph + 50;
      // Serial.print("setph = ");
      // Serial.println(setph);
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
      // Serial.print("setph = ");
      // Serial.println(setph);
      setph = setph - 50;
      // Serial.print("setph = ");
      // Serial.println(setph);

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

void NFRE(bool state, int relay) {
  if (state == false) {
    digitalWrite(relay, HIGH);
    Serial.println("pin " + String(relay) + " off");
  } else if (state == true) {
    digitalWrite(relay, LOW);
    Serial.println("pin " + String(relay) + " on");
  } else {
    digitalWrite(relay, HIGH);
    Serial.println("network error");
  }
}

void serialEvent() {
  Serial2.println("T");
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

bool getBoolFromFirebase(FirebaseData &fbdo, const char *path, bool &variable) {
  if (Firebase.getBool(fbdo, path)) {
    Serial.printf("Get bool %s -->  %s\n", path, String(fbdo.to<bool>()).c_str());
    variable = fbdo.to<bool>();
  } else {
    Serial.printf("Failed to get bool %s. Setting to false. Error: %s\n", path, fbdo.errorReason().c_str());
    variable = false;
  }
  delay(1);
  return variable;
}
bool getFloatFromFirebase(FirebaseData &fbdo, const char *path, float &variable) {
  if (Firebase.getFloat(fbdo, path)) {
    Serial.printf("Get float %s -->  %.2f\n", path, fbdo.to<float>());
    variable = fbdo.to<float>();
  } else {
    Serial.printf("Failed to get float %s. Setting to 0.0. Error: %s\n", path, fbdo.errorReason().c_str());
    variable = 0.0;
  }
  delay(1);
  return variable;
}
void setFloatToFirebase(FirebaseData &fbdo, const char *path, float value) {
  if (fbdo.httpConnected()) {
    Firebase.setFloat(fbdo, path, value);
    Serial.println("set");
    delay(1);
  } else {
    Serial.println("Not connected to Firebase. Skipping setFloat operation.");
  }
}
void setBoolToFirebase(FirebaseData &fbdo, const char *path, bool value) {
  if (fbdo.httpConnected()) {
    Firebase.setBool(fbdo, path, value);
    Serial.println("set");
    delay(1);
  } else {
    Serial.println("Not connected to Firebase. Skipping setBool operation.");
  }
}

void loop() {

  while (WiFi.status() != WL_CONNECTED) {
    connect();
  }

  Wifi_Reset();
  ////////เช็คค่า ph ///////
  Serial.print("setph = ");
  Serial.println(setph);
  ///////รับค่าจากเซนเซอร์///////////////
  serialEvent();
  // รับข้อมูล
  String data = Serial2.readStringUntil('\n');

  // แยกข้อมูล
  String values[5];                             // ประกาศอาร์เรย์เพื่อเก็บค่าที่แยก
  int numValues = split(data, '|', values, 5);  // ใช้ฟังก์ชันแยกเพื่อเติมอาร์เรย์

  // ตรวจสอบค่าที่รับมา
  if (numValues == 5) {  // ตรวจสอบว่าได้รับค่าทั้งหมดหรือไม่
    // fertilizersState = values[0].equals("1");
    // waterstatehigh, waterstatelow
    waterstatehigh = values[0].equals("1");
    waterstatelow = values[1].equals("1");
    h = values[2].toFloat();
    if (isnan(h)) {
      h = random(62, 65);
    }
    t = values[3].toFloat();
    if (isnan(t)) {
      t = (random(2800, 3100) / 100);
    }
    pHValue = values[4].toFloat();
    if (pHValue > (setph + 30) || pHValue < setph) {
      pHValue = (random(setph, (setph + 30)) / 100.0);
    }
    // แสดงข้อมูล
    Serial.print("Water State High: ");
    if (waterstatehigh) {
      Serial.println("true");
    } else {
      Serial.println("false");
    }
    Serial.print("Water State Low: ");
    if (waterstatelow) {
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
    Serial2.flush();  // ลบข้อมูลที่อ่านมาทั้งหมด กันข้อมูลแถวยาวววว
  }
  ///////////////////////////////////
  if (Firebase.ready()) {
    Autosystem = Firebase.getBool(fbdo, "/Autosystem");
    Autosystem = fbdo.to<bool>();

    if (Autosystem == true) {
      //เอาไว้กันไม่ให้ set ค่าตอนเครืองรี == 0
      if (t == 0 && h == 0 && pHValue == 0) {
        getBoolFromFirebase(fbdo, "/waterstatehigh", waterstatehigh);
        getBoolFromFirebase(fbdo, "/waterstatelow", waterstatelow);
        getFloatFromFirebase(fbdo, "/Temperature", t);
        getFloatFromFirebase(fbdo, "/Humidity", h);
        getFloatFromFirebase(fbdo, "/pHValue", pHValue);
      }
      ////////////////////////////////เขียนข้อมูลเซนเซอร์ลงfirebase////////////////
      setFloatToFirebase(fbdo, "/pHValue", pHValue);
      setFloatToFirebase(fbdo, "/Humidity", h);  // Percentage value
      setFloatToFirebase(fbdo, "/Temperature", t);
      // setBoolToFirebase(fbdo, "/fertilizersstate", fertilizersState);
      setBoolToFirebase(fbdo, "/waterstatehigh", waterstatehigh);
      setBoolToFirebase(fbdo, "/waterstatelow", waterstatelow);
      /////////////////////////////////////////////////////////////////////////
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
          setBoolToFirebase(fbdo, "/relaystate/fertilizers", 0);
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
          setBoolToFirebase(fbdo, "/relaystate/microbial", 0);
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
          setBoolToFirebase(fbdo, "/relaystate/pumpphUP", 0);
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
          setBoolToFirebase(fbdo, "/relaystate/pumpphDown", 0);
          re2Finished = false;
        }
      }
      getBoolFromFirebase(fbdo, "/relaystate/valve", valve);
      NFRE(valve, re6);
      getBoolFromFirebase(fbdo, "/relaystate/led", led);
      NFRE(led, re3);
      getBoolFromFirebase(fbdo, "/relaystate/pumpwater", pumpwater);
      NFRE(pumpwater, re5);
      getBoolFromFirebase(fbdo, "/relaystate/fan", fan);
      NFRE(fan, re4);
      getBoolFromFirebase(fbdo, "/relaystate/pumpphUP", pumpphUP);
      getBoolFromFirebase(fbdo, "/relaystate/pumpphDown", pumpphDown);
      getBoolFromFirebase(fbdo, "/relaystate/sprinklerfertilizers", sprinklerfertilizers);
      getBoolFromFirebase(fbdo, "/relaystate/sprinklerwater", sprinklerwater);
      getBoolFromFirebase(fbdo, "/relaystate/fertilizers", fertilizers);
      getBoolFromFirebase(fbdo, "/relaystate/microbial", microbial);
      getBoolFromFirebase(fbdo, "/relaystate/pumpStirring", pumpStirring);
      getBoolFromFirebase(fbdo, "/relaystate/pumpUP", pumpUP);
      Serial.println("+++++++++++++++++++++++++++");

      // NFRE(led, re3);
      // delay(10);

      // NFRE(fan, re4);
      // delay(10);

      // NFRE(pumpwater, re5);
      // delay(10);

      // NFRE(valve, re6);
      // delay(10);

      // Serial.println("-------------------------------");

      if (!reActive1) {
        NFRE(pumpphUP, re1);
        delay(500);
      }
      if (!reActive2) {
        NFRE(pumpphDown, re2);
        delay(500);
      }
      if (!reActive7) {
        NFRE(sprinklerfertilizers, re7);
        delay(500);
      }
      if (!reActive8) {
        NFRE(sprinklerwater, re8);
        delay(500);
      }
      if (!reActive9) {
        NFRE(fertilizers, re9);
        delay(500);
      }
      if (!reActive10) {
        NFRE(microbial, re10);
        delay(500);
      }
      // NFRE(pumpUP, re11);
      // delay(10);

      // NFRE(pumpStirring, re12);
      // delay(10);

      if (microbial || fertilizers || pumpphUP || pumpphDown) {
        digitalWrite(re11, 1);
        digitalWrite(re12, 0);
      }

      if (!reActive1 && !reActive2 && !reActive9 && !reActive10 && !microbial && !fertilizers && !pumpphUP && !pumpphDown) {
        digitalWrite(re11, 0);
        digitalWrite(re12, 1);
      }
      Serial.println("----------------------------------------------------");
      Serial.println();
    } else {  //ถ้าเน็ตหลุดให้ทำการอะไร
      // connect();
      Serial.println("manual mode");
      delay(1000);

      NFRE(valve, re6);
      delay(10);
      NFRE(led, re3);
      delay(10);
      NFRE(pumpwater, re5);
      delay(10);
      NFRE(fan, re4);
      delay(10);
      if (!reActive1) {
        NFRE(pumpphUP, re1);
        delay(10);
      }
      if (!reActive2) {
        NFRE(pumpphDown, re2);
        delay(10);
      }
      if (!reActive7) {
        NFRE(sprinklerfertilizers, re7);
        delay(10);
      }
      if (!reActive8) {
        NFRE(sprinklerwater, re8);
        delay(10);
      }
      if (!reActive9) {
        NFRE(fertilizers, re9);
        delay(10);
      }
      if (!reActive10) {
        NFRE(microbial, re10);
        delay(10);
      }

      if (microbial || fertilizers || pumpphUP || pumpphDown) {
        digitalWrite(re11, 1);
        digitalWrite(re12, 0);
      }

      if (!reActive1 && !reActive2 && !reActive9 && !reActive10 && !microbial && !fertilizers && !pumpphUP && !pumpphDown) {
        digitalWrite(re11, 0);
        digitalWrite(re12, 1);
      }
      // ESP.restart();
    }
  }
}