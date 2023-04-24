#include <Arduino.h>

class CarbonMonoxideSensor {
  private:
    int sensorPin;

  public:
    CarbonMonoxideSensor(int pin);
    bool isCarbonMonoxideDetected();
    void printCarbonMonoxideStatus();
    int getCarbonMonoxideLevelStatus();
};
