#include <Arduino.h>
#include <IRremote.hpp>

#define IR_RECEIVE_PIN 14rr


void setup() {
  Serial.begin(9600);

  IrReceiver.begin(IR_RECEIVE_PIN, DISABLE_LED_FEEDBACK);

  Serial.println("Ready to receive IR signals");
  Serial.println("Point the remote controller to the IR receiver and press!");
}

void loop() {
  if (IrReceiver.decode()) {  // Grab an IR code
        // At 115200 baud, printing takes 200 ms for NEC protocol and 70 ms for NEC repeat
        Serial.println(); // blank line between entries
        Serial.println(); // 2 blank lines between entries
        IrReceiver.printIRResultShort(&Serial);
        // Check if the buffer overflowed
        if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_WAS_OVERFLOW) {
            Serial.println("Try to increase the \"RAW_BUFFER_LENGTH\" value");
            // see also https://github.com/Arduino-IRremote/Arduino-IRremote#compile-options--macros-for-this-library
        } else {
            if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
                Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
            }
            else {
              
              Serial.println();
              IrReceiver.printIRSendUsage(&Serial);rrr
              Serial.println();
              Serial.println(F("Raw result in internal ticks (50 us) - with leading gap"));
              IrReceiver.printIRResultRawFormatted(&Serial, false); // Output the results in RAW format
              Serial.println(F("Raw result in microseconds - with leading gap"));
              IrReceiver.printIRResultRawFormatted(&Serial, true);  // Output the results in RAW format
              Serial.println();                               // blank line between entries
              Serial.print(F("Result as internal 8bit ticks (50 us) array - compensated with MARK_EXCESS_MICROS="));
              Serial.println(MARK_EXCESS_MICROS);
              IrReceiver.compensateAndPrintIRResultAsCArray(&Serial, false); // Output the results as uint8_t source code array of ticks
              Serial.print(F("Result as microseconds array - compensated with MARK_EXCESS_MICROS="));
              Serial.println(MARK_EXCESS_MICROS);
              IrReceiver.compensateAndPrintIRResultAsCArray(&Serial, true); // Output the results as uint16_t source code array of micros
              IrReceiver.printIRResultAsCVariables(&Serial);  // Output address and data as source code variables

              IrReceiver.compensateAndPrintIRResultAsPronto(&Serial);
            }
        }
        IrReceiver.resume();                            // Prepare for the next value
    }
}