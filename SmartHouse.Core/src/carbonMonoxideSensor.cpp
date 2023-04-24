#include "Arduino.h"
#include "carbonMonoxideSensor.h"

CarbonMonoxideSensor::CarbonMonoxideSensor(int pin){
  sensorPin = pin;
    pinMode(sensorPin, INPUT);
}

bool CarbonMonoxideSensor::isCarbonMonoxideDetected() {
  int sensorValue = CarbonMonoxideSensor::getCarbonMonoxideLevelStatus();
  if (sensorValue == 1) 
    return true;
  
  return false;
}

void CarbonMonoxideSensor::printCarbonMonoxideStatus(){
  Serial.print("\ncarbon monoxide status: ");
  Serial.print(CarbonMonoxideSensor::getCarbonMonoxideLevelStatus());
  Serial.print('\n');
}

int CarbonMonoxideSensor::getCarbonMonoxideLevelStatus(){
  return digitalRead(sensorPin);
}
