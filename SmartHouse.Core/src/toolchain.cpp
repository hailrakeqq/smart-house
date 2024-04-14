#include "../include/toolchain.h"

String toolchain::readFromEEPROM(int address) {
  String data = "";
  char character = EEPROM.read(address);

  while (character != '\0' && address < 100) { // eeprom size
    data += character;
    address++;
    character = EEPROM.read(address);
  }

  return data;
}

void toolchain::writeToEEPROM(String data, int address) {
  for (int i = 0; i < data.length(); i++) {
    EEPROM.write(address + i, data[i]);
  }
  EEPROM.write(address + data.length(), '\0');
  EEPROM.commit();
}

void toolchain::clearEEPROM() {
  for (int i = 0; i < 512; i++) // 512 == eeprom size
    EEPROM.write(i, 0);

  EEPROM.commit();
}

String toolchain::createJSON(StaticJsonDocument<128> doc){
    String json;
    serializeJson(doc, json);

    return json;
}