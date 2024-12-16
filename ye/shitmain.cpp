#include <Arduino.h>

#define CONTACT_PIN 10
#define RELAY_OFF_PIN 14
#define RELAY_ON_PIN 13


void setup() {
  Serial.begin(9600);
  

  pinMode(CONTACT_PIN, INPUT);
  pinMode(RELAY_ON_PIN, OUTPUT);
  pinMode(RELAY_OFF_PIN, OUTPUT);
}

void loop() {

    byte state = digitalRead(CONTACT_PIN);
    if(state == HIGH) {
        Serial.println("button push");
        digitalWrite(RELAY_OFF_PIN, HIGH);
        delay(2000);
        digitalWrite(RELAY_OFF_PIN, LOW);
    }
    delay(100);
}