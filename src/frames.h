#include <Arduino.h>

const uint8_t OFF_FRAME[25] = {67,65, 27,7, 27,8, 9,24, 10,24, 10,24, 9,25, 9,24, 10,24, 10,24, 9,25, 9,24, 10};  // Protocol=PulseWidth Raw-Data=0x3 12 bits LSB first
const uint8_t LOW_FRAME[23] = {27,8, 26,8, 10,24, 9,25, 9,24, 10,24, 9,25, 9,24, 10,24, 10,24, 9,25, 9};  // Protocol=PulseWidth Raw-Data=0x1 11 bits LSB first
const uint8_t MED_FRAME[23] = {27,8, 27,8, 9,25, 9,24, 10,24, 10,24, 10,24, 9,25, 9,25, 27,7, 10,24, 10};  // Protocol=PulseWidth Repeat gap=7000us Raw-Data=0x101 11 bits LSB first
const uint8_t HIG_FRAME[23] = {27,7, 27,8, 9,24, 10,24, 10,24, 9,25, 9,24, 10,24, 10,24, 9,25, 9,24, 10};  // Protocol=PulseWidth Repeat gap=86650us Raw-Data=0x1 11 bits LSB first