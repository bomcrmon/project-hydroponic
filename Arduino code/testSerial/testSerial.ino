#define led1 33
#define led2 25
#define led3 26
#define relay 23
#define relay2 22
#define relay3 21

char key = '0';
int x = 0;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  Serial.begin(9600);
  Serial.println("my  arduino");
  digitalWrite(led1, 0);
  digitalWrite(led2, 0);
  digitalWrite(led3, 0);
  digitalWrite(relay, 1);
  digitalWrite(relay2, 1);
  digitalWrite(relay3, 1);
}

void loop() {
  if (Serial.available() > 0) {
    key = Serial.read();
    Serial.print("key : ");
    Serial.println(key);
  }
  if (key == '0') {
    if (digitalRead(led1) == 0 || digitalRead(led2) == 0 || digitalRead(led3) == 0) {
      digitalWrite(led1, 1);
      digitalWrite(led2, 1);
      digitalWrite(led3, 1);
      Serial.println("LED ALL ON!!");
      delay(250);

    } else if (digitalRead(led1) == 1 || digitalRead(led2) == 1 || digitalRead(led3) == 1) {
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      Serial.println("LED ALL OFF!!");
      delay(250);
    }
  } else if (key == '1') {
    if (digitalRead(led1) == 0) {
      digitalWrite(led1, 1);
      Serial.println("LED1 ON!!");
      delay(250);

    } else if (digitalRead(led1) == 1) {
      digitalWrite(led1, 0);
      Serial.println("LED1 OFF!!");
      delay(250);
    }
  } else if (key == '2') {
    if (digitalRead(led2) == 0) {
      digitalWrite(led2, 1);
      Serial.println("LED2 ON!!");
      delay(250);

    } else if (digitalRead(led2) == 1) {
      digitalWrite(led2, 0);
      Serial.println("LED2 OFF!!");
      delay(250);
    }
  } else if (key == '3') {
    if (digitalRead(led3) == 0) {
      digitalWrite(led3, 1);
      Serial.println("LED3 ON!!");
      delay(250);

    } else if (digitalRead(led3) == 1) {
      digitalWrite(led3, 0);
      Serial.println("LED3 OFF!!");
      delay(250);
    }
  } else if (key == '4') {
    int allL[] = { led1, led2, led3 };
    for (int j = 1; j <= 10; j++) {
      Serial.println("loop " + String(j) + " !!");
      delay(1000);
      for (int i = 0; i < 3; i++) {
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        digitalWrite(allL[i], 1);
        Serial.println("LED " + String(i + 1) + " ON");
        delay(250);
      }
    }
  } else if (key == '5') {
    int allL[] = { led1, led2, led3 };
    for (int j = 1; j <= 10; j++) {
      for (int i = 0; i < 3; i++) {
        digitalWrite(allL[i], 1);
        delay(250);
      }
      for (int i = 2; i >= 0; i--) {
        digitalWrite(allL[i], 0);
        delay(250);
      }
    }
  }
  // if (key == '6') {
  //   int allL[] = { led1, led2, led3 };
  //   for (int j = 1; j <= 10; j++) {
  //     for (int i = 0; i < 3; i++) {
  //       digitalWrite(led1, LOW);
  //       digitalWrite(led2, LOW);
  //       digitalWrite(led3, LOW);
  //       digitalWrite(allL[i], 1);
  //       delay(250);
  //     }
  //     for (int i = 2; i >= 0; i--) {
  //       digitalWrite(led1, LOW);
  //       digitalWrite(led2, LOW);
  //       digitalWrite(led3, LOW);
  //       digitalWrite(allL[i], 1);
  //       delay(250);
  //     }
  //   }
  // }
  // if (key == '7') {
  //   int allL[] = { led1, led2, led3, led2, led1 };
  //   for (int j = 1; j <= 10; j++) {
  //     for (int i = 0; i < 5; i++) {
  //       digitalWrite(led1, LOW);
  //       digitalWrite(led2, LOW);
  //       digitalWrite(led3, LOW);
  //       digitalWrite(allL[i], 1);
  //       delay(250);
  //     }
  //   }
  // }
  else if (key == '6') {
    if (digitalRead(relay) == 0) {
      digitalWrite(relay, 1);
      delay(250);

    } else if (digitalRead(relay) == 1) {
      digitalWrite(relay, 0);
      delay(250);
    }
  } else if (key == '7') {
    if (digitalRead(relay2) == 0) {
      digitalWrite(relay2, 1);
      delay(250);

    } else if (digitalRead(relay2) == 1) {
      digitalWrite(relay2, 0);
      delay(250);
    }
  } else if (key == '8') {
    if (digitalRead(relay3) == 0) {
      digitalWrite(relay3, 1);
      delay(250);

    } else if (digitalRead(relay3) == 1) {
      digitalWrite(relay3, 0);
      delay(250);
    }
  } else if (key == '9') {
    if (digitalRead(relay) == 0 || digitalRead(relay2) == 0 || digitalRead(relay3) == 0) {
      digitalWrite(relay, 1);
      // delay(250);
      digitalWrite(relay2, 1);
      // delay(250);
      digitalWrite(relay3, 1);
      delay(250);
    } else if (digitalRead(relay) == 1 || digitalRead(relay2) == 1 || digitalRead(relay3) == 1) {
      digitalWrite(relay, 0);
      // delay(250);
      digitalWrite(relay2, 0);
      // delay(250);
      digitalWrite(relay3, 0);
      delay(250);
      
  } else {
  }
}
