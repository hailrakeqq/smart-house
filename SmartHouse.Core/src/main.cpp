#include "../include/toolchain.h"
#include "../include/waterSensor.h"
#include "../include/httpClient.h"
#include "../include/uptime.h"
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <Servo.h>
#include <WiFiClient.h>
#include <map>
#include <WiFiManager.h>
#include <Servo.h>

#pragma region setting_up
//Comment this string to use solenoid valve
#define IS_SERVO_USE 1

int button = D6;
WiFiManager wm;
WiFiManagerParameter email = WiFiManagerParameter("email", "email", "", 40); 
WiFiManagerParameter api_address = WiFiManagerParameter("api_address", "api ip dns name address", "", 40); 

ESP8266WebServer server(80);
IPAddress localIP;
String externalIP;

WiFiClient client;
HttpClient* httpClient;

#pragma region servo

Servo servo;
#define CLOSE_ANGLE 0
#define OPEN_ANGLE 80
bool isServoOpen;

#pragma endregion

//Variable for save uptime
unsigned long startTime;
unsigned long currentUpTime;

#pragma endregion

bool isDetectWater(int waterSensor_ADC_value){
  return waterSensor_ADC_value > 100 ? true : false;
}

void closeValve(){}

void openValve(){}

void closeServo(){
  auto currentAngle = servo.read();
  if(currentAngle != CLOSE_ANGLE){
    servo.write(CLOSE_ANGLE);
    isServoOpen = false;
  }
}

void openServo(){
  auto currentAngle = servo.read();
  if(currentAngle != OPEN_ANGLE){
    servo.write(OPEN_ANGLE);
    isServoOpen = true;
  }
}

double GetWaterLevel(int waterSensor_ADC){
  return ((-1) * ((float)(waterSensor_ADC * 5) / 1024));
}

#pragma region serverFunction
void handleClose() {
  #ifdef IS_SERVO_USE
    closeServo();
  #else
    closeValve();
  #endif

  server.send(200, "text/plain", "Close");
}

void handleOpen() {
  #ifdef IS_SERVO_USE
    openServo();
  #else
    openValve();
  #endif

  server.send(200, "text/plain", "Open");
}
#pragma endregion

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("\n Starting");

  pinMode(button, INPUT);
  
  #pragma region wifi settings
  wm.addParameter(&email);
  wm.addParameter(&api_address);
  wm.setConfigPortalTimeout(30);
  bool res = wm.autoConnect("Smarthouse", "11111111");
  if (!res)
    Serial.println("Failed to connect or hit timeout");
  else
    Serial.println("connected...yeey :)");
  #pragma endregion

  httpClient = new HttpClient(client, api_address.getValue(), email.getValue());
  
  //HTTP server for handle user request
  server.on("/open", handleOpen);
  server.on("/close", handleClose);
  server.begin();
  Serial.println("HTTP server started");

  servo.attach(D4);

  localIP = WiFi.localIP();  
  externalIP = httpClient->getExternalIP();
}

// void checkButton() { // TODO:додати закриття відкриття соляноїда
//   if (digitalRead(button) == LOW) {
//     delay(50);
//     if (digitalRead(button) == LOW) {
//       Serial.println("Button Pressed");
//       //TODO: add if 1 or doble clicked => close valve
//       delay(3000);
//       if (digitalRead(button) == LOW) {
//         Serial.println("Button Held");
//         Serial.println("Erasing Config, restarting");
//         wm.resetSettings();
//         ESP.restart();
//       }

//       // start portal w delay
//       Serial.println("Starting config portal");
//       wm.setConfigPortalTimeout(120);
//       wm.addParameter(&email);

//       if (!wm.startConfigPortal("Smarthouse", "11111111")) {
//         Serial.println("failed to connect or hit timeout");
//         delay(3000);
//         ESP.restart();
//       } else {
//         Serial.println("connected...yeey :)");
//       }
//     }
//   }
// }

unsigned long lastButtonPressTime = 0;
const int doubleClickDelay = 500;

void checkButton() {
  if (digitalRead(button) == LOW) {
    delay(50);
    if (digitalRead(button) == LOW) {
      unsigned long currentMillis = millis();

      // Перевірка на подвійний натискання
      if (currentMillis - lastButtonPressTime <= doubleClickDelay) {
        Serial.println("Double Click Detected");
        if(isServoOpen){
          #ifdef IS_SERVO_USE
            isServoOpen ? closeServo() : openServo();
          #else
            isServoOpen ? closeValve() : openValve();
          #endif
        }
      } else {
        Serial.println("Button Pressed");
      }

      lastButtonPressTime = currentMillis;

      delay(3000);
      if (digitalRead(button) == LOW) {
        Serial.println("Button Held");
        Serial.println("Erasing Config, restarting");
        wm.resetSettings();
        ESP.restart();
      }

      // start portal w delay
      Serial.println("Starting config portal");
      wm.setConfigPortalTimeout(120);
      wm.addParameter(&email);

      if (!wm.startConfigPortal("Smarthouse", "11111111")) {
        Serial.println("failed to connect or hit timeout");
        delay(3000);
        ESP.restart();
      } else {
        Serial.println("connected...yeey :)");
      }
    }
  }
}

void loop() {
  currentUpTime = millis();  
  unsigned long uptimeInSeconds = (currentUpTime - startTime) / 1000;

  checkButton();
  
  int waterSensor_ADC_value = analogRead(A0);
  bool isWaterDetect = isDetectWater(waterSensor_ADC_value);
  double waterLvl = GetWaterLevel(waterSensor_ADC_value);

  if(isWaterDetect){

    #ifdef IS_SERVO_USE
      isServoOpen ? closeServo() : openServo();
    #else
      isServoOpen ? closeValve() : openValve();
    #endif

    httpClient->sendDetectedMessage(waterLvl); 
  }

  mytime::uptime uptime = mytime::getCurrentUptime(uptimeInSeconds);
  httpClient->sendState(waterLvl,isServoOpen, &uptime);
  
  delay(1000);
}
