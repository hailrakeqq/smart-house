#include "include.h"

const char* ssid = "busya";
const char* password = "0677170801";

const String baseServerURL = "http://192.168.0.15:5198";

WaterSensor waterSensor(A0);
servoMotor servo(2); // 2 ==== 4 nodemcu
ESP8266WebServer server(4000);

unsigned long lastTime = 0;
unsigned long timerDelay = 10000;

void handle_close() 
{  
  servo.closeServo();
  server.send(200, "text/plain", "servo was closed");
}

void handle_open() 
{
  servo.openServo();
  server.send(200, "text/plain", "servo was opened");
}

void handle_sendServoStatus(){
  String json;
  StaticJsonDocument<32> doc;
  doc["ServoStatus"] = servo.getServoStatus(); 
  serializeJson(doc, json);
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
  // servo.attach(2); //D4 nodemcu
  
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/close", handle_close);
  server.on("/open", handle_open);
  server.on("/getServoStatus", handle_sendServoStatus);

  server.begin();

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
  server.handleClient();
  waterSensorLifetimeCycle();
}

