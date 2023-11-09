#include <Arduino.h>
#include <IRremote.hpp>
#include "./frames.h"


#define IR_SEND_PIN 4

void setup() {
  Serial.begin(9600);

  IrSender.begin(IR_SEND_PIN); // Start with IR_SEND_PIN as send pin and enable feedback LED at default feedback LED pin
}

void loop() {

  /*
    * Send byte data direct from FLASH
    * Note the approach used to automatically calculate the size of the array.
    */
  IrSender.sendRaw_P(OFF_FRAME, sizeof(OFF_FRAME) / sizeof(OFF_FRAME[0]), NEC_KHZ);

  delay(1000); // delay must be greater than 5 ms (RECORD_GAP_MICROS), otherwise the receiver sees it as one long signal
    
  Serial.println(F("Send NEC 16 bit address 0x0102, 8 bit data 0x34 with generated timing"));
  Serial.flush();
  IrSender.sendNEC(0x0102, 0x34, 0);

  delay(3000);
}