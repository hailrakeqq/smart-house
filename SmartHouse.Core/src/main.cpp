#include "include.h"
#define CHANGESTATETYPE "change hardware state";
#define GETSTATUSTYPE "get status";

const char* ssid = "busya";
const char* password = "0677170801";
const int jsonObjectCapacity = JSON_OBJECT_SIZE(4);

const String baseServerURL = "http://192.168.0.15:5198";

WaterSensor waterSensor(A0);
CarbonMonoxideSensor carbonMonoxideSensor(0); // 0 == d3
servoMotor servo(2); // 2 == d4 nodemcu

ESP8266WebServer server(4000);

unsigned long lastTime = 0;
unsigned long timerDelay = 10000;

void handle_close() 
{  
  String json;
  StaticJsonDocument<jsonObjectCapacity> doc;

  servo.closeServo();

  doc["type"] = CHANGESTATETYPE;
  doc["timestamp"] = "";
  doc["message"] = "servo was closed";
  serializeJson(doc, json);

  server.send(200, "application/json", json);
}

void handle_open() 
{
  String json;
  StaticJsonDocument<jsonObjectCapacity> doc;

  servo.openServo();

  doc["type"] = CHANGESTATETYPE;
  doc["timestamp"] = "";
  doc["message"] = "servo was opened";
  serializeJson(doc, json);

  server.send(200, "application/json", json);
}

void handle_sendServoStatus(){
  String json;
  StaticJsonDocument<jsonObjectCapacity> doc;

  doc["type"] = GETSTATUSTYPE;
  doc["timestamp"] = "";
  doc["message"] = servo.getServoStatus();
  serializeJson(doc, json);
  Serial.print(json);
  server.send(200, "application/json", json);
}

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

  server.on("/close", handle_close);
  server.on("/open", handle_open);
  server.on("/getServoStatus", handle_sendServoStatus);

  server.begin();

  randomSeed(analogRead(0));
  
}

void carbonMonoxideSensorLifetimeCycle(){
  carbonMonoxideSensor.printCarbonMonoxideStatus();

  if(carbonMonoxideSensor.isCarbonMonoxideDetected()){
     Serial.println("Carbon monoxide was Detected!!!");
     httpClient::sendDetectedMessageToServer("carbonMonoxide");
  }
   delay(10000);
}

void waterSensorLifetimeCycle() 
{
  waterSensor.printWaterLevel();
 
  if (waterSensor.isWaterDetected()){
    Serial.println("Water was Detected!!!");
    httpClient::sendDetectedMessageToServer("water");
  }
  delay(10000);
}

void loop()
{
  server.handleClient();
  waterSensorLifetimeCycle();
  carbonMonoxideSensorLifetimeCycle();
}
