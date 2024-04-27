#ifndef TOOLCHAIN_H
#define TOOLCHAIN_H

#include <Arduino.h>
#include <EEPROM.h>
#include <ArduinoJson.h>
#include "uptime.h"

namespace toolchain {

String readFromEEPROM(int address);
void writeToEEPROM(String data, int address);
void clearEEPROM();
String createJSON(StaticJsonDocument<128> doc);
String getState(double waterLvl, bool valveState, mytime::uptime* uptime, String userEmailAddress, String localIP, String externalIP);
} // namespace toolchain

#endif
