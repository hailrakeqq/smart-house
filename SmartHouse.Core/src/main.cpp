#include "include.h"

const char* ssid = "busya";
const char* password = "0677170801";

const String baseServerURL = "http://192.168.0.15:5198";

WaterSensor waterSensor(A0);
unsigned long lastTime = 0;
unsigned long timerDelay = 10000;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  randomSeed(analogRead(0));
}

void waterSensorLifetimeCycle() 
{
  waterSensor.printWaterLevel();
 
  if (waterSensor.isWaterDetected()){
    Serial.println("Water Detect!!!");
    httpClient::sendWaterDetectedMessageToServer();
  }
  delay(10000);
}

void loop()
{
  waterSensorLifetimeCycle(); 
}
