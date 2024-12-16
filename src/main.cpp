#include <Arduino.h>
#include <IRremote.hpp>
#include "frames.h"

#define TRIGGER_HOT_PIN 8

#define IR_SEND_PIN 47
#define IR_SEND_DUTY_CYCLE_PERCENT 33
#define IR_FREQUENCY 38

#define DEBOUNCE_DELAY 50

size_t onFrameSize;
size_t offFrameSize;

int on_sent = 0;
int off_sent = 0;
int send_count = 10;

unsigned long lastDebounceTime = 0;
int lastButtonState = LOW;

void sendOn() {
  Serial.println(F("Sending ON"));
  for(int i = 0; i < send_count; i++) {
    IrSender.sendRaw(FRAME_ON_MEDIUM, onFrameSize, IR_FREQUENCY);
    delay(200);
  }
  Serial.println(F("Sending ON [OK]"));
  off_sent = 0;
  on_sent = 1;
  delay(2000);
}

void sendOff() {
  Serial.println(F("Sending OFF"));
  for(int i = 0; i < send_count; i++) {
    IrSender.sendRaw(FRAME_OFF, offFrameSize, IR_FREQUENCY);
    delay(200);
  }
  Serial.println(F("Sending OFF [OK]"));
  off_sent = 1;
  on_sent = 0;
  delay(2000);
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIGGER_HOT_PIN, INPUT);
  IrSender.begin(IR_SEND_PIN, true, LED_BUILTIN);

  on_sent = 0;
  off_sent = 0;
  
  onFrameSize = sizeof(FRAME_ON_MEDIUM) / sizeof(uint16_t);
  offFrameSize = sizeof(FRAME_OFF) / sizeof(uint16_t);
}

void loop() {
  // Read the current state of the trigger pin
  int reading = digitalRead(TRIGGER_HOT_PIN);

  // Check if the state has changed
  if (reading != lastButtonState) {
    lastDebounceTime = millis(); // Reset debounce timer
  }

  // Only act if enough time has passed since the last change
  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    if (reading == HIGH && on_sent == 0) {
      sendOn();
    } else if (reading == LOW && off_sent == 0) {
      sendOff();
    }
  }

  // Save the current state as the last state for the next loop iteration
  lastButtonState = reading;
}

