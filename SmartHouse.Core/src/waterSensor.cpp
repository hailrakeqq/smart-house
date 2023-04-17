#include "Arduino.h"
#include "waterSensor.h"

WaterSensor::WaterSensor(int pin) {
  sensorPin = pin;
  pinMode(sensorPin, INPUT);
}

bool WaterSensor::isWaterDetected() {
  int sensorValue = analogRead(sensorPin);
  if (sensorValue > 350) 
    return true;
  
  return false;
}

int WaterSensor::getWaterLevelValue(){
  return analogRead(sensorPin);
}

void WaterSensor::printWaterLevel(){
  Serial.print("water level: ");
  Serial.print(WaterSensor::getWaterLevelValue());
  Serial.print('\n');
}
