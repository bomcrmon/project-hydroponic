#include <WiFiManager.h>
WiFiManager wm;

#define SWrwf 32
void setup() {
  Serial.begin(115200);
  pinMode(SWrwf, INPUT_PULLUP);
  if (wm.autoConnect("@hydroponic farm")) {
    Serial.println("");
    Serial.println("Connected already WiFi : ");
    Serial.println("OP Address : ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("failed to connect");
    delay(1000);
    ESP.restart();
  }
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection lost. Reconnecting...");
    if (wm.autoConnect("@hydroponic farm")) {
      Serial.println("Reconnected to WiFi.");
      Serial.println("OP Address : ");
      Serial.println(WiFi.localIP());
    } else {
      Serial.println("Failed to reconnect to WiFi.");
    }
  }
  Wifi_Reset();
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
