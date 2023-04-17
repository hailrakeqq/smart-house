#ifndef WATER_SENSOR_H
#define WATER_SENSOR_H

#include <Arduino.h>

class WaterSensor {
  private:
    int sensorPin;

  public:
    WaterSensor(int pin);
    bool isWaterDetected();
    void printWaterLevel();
    int getWaterLevelValue();
};

#endif
