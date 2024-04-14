#ifndef TOOLCHAIN_H
#define TOOLCHAIN_H

#include <Arduino.h>
#include <EEPROM.h>
#include <ArduinoJson.h>

namespace toolchain {

String readFromEEPROM(int address);
void writeToEEPROM(String data, int address);
void clearEEPROM();
String createJSON(StaticJsonDocument<128> doc);

} // namespace toolchain

#endif
