#include <FirebaseESP32.h>
#define led1 33
#define led2 25
int x;

void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
}

void loop() {
  Serial.print("Scan start ... ");
  int n = WiFi.scanNetworks();
  Serial.print(n);
  Serial.println(" network(s) found");
  // for (int i = 0; i < n; i++) {
  //   // x = (i % 2);
  //   if ((i % 2) == 0) {
  //     digitalWrite(led1, 1);
  //     delay(500);
  //     digitalWrite(led1, 0);
  //     delay(500);
  //   } else if ((i % 2) == 1) {
  //     digitalWrite(led2, 1);
  //     delay(500);
  //     digitalWrite(led2, 0);
  //     delay(500);
  //   }
  // }
  for (int i = 0; i < n; i++) {
    if ((i % 2) == 0) {
      digitalWrite(led1, 1);
      delay(500);
      digitalWrite(led1, 0);
      delay(500);
      Serial.println(WiFi.SSID(i));
    } else if ((i % 2) == 1) {
      digitalWrite(led2, 1);
      delay(500);
      digitalWrite(led2, 0);
      delay(500);
      Serial.println(WiFi.SSID(i));
    }
  }
  Serial.println();
  for (int i = 0; i < n; i++) {
    digitalWrite(led1, 1);
    delay(500);
    digitalWrite(led1, 0);
    delay(500);
  }
  delay(10000);
}