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
#include <FS.h>
#include <WiFiManager.h>
#include <Servo.h>

#pragma region setting_up
//Comment this define to use solenoid valve
#define IS_SERVO_USE 1

#define SERVO_DELAY 100
#define ANGLE_THRESHOLD 2

int buttonPin = D6;
WiFiManager wm;
char* defaultEmail = "boklanura@gmail.com";
char* defaultApiAddress = "http://192.168.0.3:5198";
WiFiManagerParameter email = WiFiManagerParameter("email", "email", defaultEmail, 64); 
WiFiManagerParameter api_address = WiFiManagerParameter("api_address", "api ip address or dns name", defaultApiAddress, 64); 

ESP8266WebServer server(80);
IPAddress localIP;
String externalIP;

WiFiClient client;
HttpClient* httpClient;

#pragma region servo

Servo servo;
#define CLOSE_ANGLE 0
#define OPEN_ANGLE 60
bool isServoOpen = true;

#pragma endregion

//Variable for save uptime
unsigned long startTime;
unsigned long currentUpTime;

unsigned long uptimeInSeconds = (currentUpTime - startTime) / 1000;
mytime::uptime uptime = mytime::getCurrentUptime(uptimeInSeconds);

  
int waterSensor_ADC_value;
bool isWaterDetect;
double waterLvl;


#pragma endregion

bool isDetectWater(int waterSensor_ADC_value){
  return waterSensor_ADC_value > 100 ? true : false;
}

void closeValve(){}

void openValve(){}

void closeServo() {
  if (isServoOpen) {
    servo.write(CLOSE_ANGLE);
    delay(SERVO_DELAY);
    auto currentAngle = servo.read();
    while (abs(currentAngle - CLOSE_ANGLE) > ANGLE_THRESHOLD) {
      delay(10);
      currentAngle = servo.read(); 
    }
    isServoOpen = false;
    Serial.println("Servo was closed");
  }
}

void openServo() {
  if (!isServoOpen) {
    servo.write(OPEN_ANGLE);
    delay(SERVO_DELAY);
    auto currentAngle = servo.read();
    while (abs(currentAngle - OPEN_ANGLE) > ANGLE_THRESHOLD) {
      delay(10);
      currentAngle = servo.read(); 
    }
    isServoOpen = true;
    Serial.println("Servo was opened");
  }
}

double GetWaterLevel(int waterSensor_ADC){
  return (float)(waterSensor_ADC * 5) / 1024;
}

#pragma region serverFunction
void handleClose() {
  #ifdef IS_SERVO_USE
    closeServo();
  #else
    closeValve();
  #endif

  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "Close");
}

void handleOpen() {
  #ifdef IS_SERVO_USE
    openServo();
  #else
    openValve();
  #endif
  
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "Open");
}

void handleGetState() {
  String response = toolchain::getState(waterLvl, isServoOpen, &uptime, defaultEmail, localIP.toString(), externalIP);
  server.send(200, "application/json", response);
}

#pragma endregion

bool shouldSaveConfig = false;

void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("\nStarting");

  pinMode(buttonPin, INPUT);
  
  #pragma region wifi settings
  wm.setSaveConfigCallback(saveConfigCallback);
  wm.addParameter(&email);
  wm.addParameter(&api_address);
  bool res = wm.autoConnect("Smarthouse", "11111111");
  if (!res)
    Serial.println("Failed to connect or hit timeout");
  else
    Serial.println("connected...yeey :)");
  #pragma endregion

  //HTTP server for handle user request
  server.on("/open", HTTP_POST, handleOpen);
  server.on("/close", HTTP_POST, handleClose);
  server.on("/getState", HTTP_GET, handleGetState);
  server.begin();
  Serial.println("HTTP server started");

  servo.attach(D4);
  openServo();

  localIP = WiFi.localIP();  
  httpClient = new HttpClient(client, api_address.getValue(), email.getValue(), localIP);
  externalIP = httpClient->getExternalIP();
  httpClient->setExternalIP(externalIP);

  httpClient->sendDeviceIPToAPI(localIP.toString(), externalIP, defaultEmail);
}

enum ButtonState {
  IDLE,
  PRESSED,
  HELD
};

ButtonState buttonState = IDLE;
unsigned long buttonPressTime = 0;

void checkButton() {
  bool buttonPressed = (digitalRead(buttonPin) == LOW);

  switch (buttonState) {
    case IDLE:
      if (buttonPressed) {
        buttonState = PRESSED;
        buttonPressTime = millis();
      }
      break;

    case PRESSED:
      if (buttonPressed && (millis() - buttonPressTime >= 50)) {
        buttonState = HELD;
        Serial.println("Button Held");
        Serial.println("Erasing Config, restarting");
        wm.resetSettings();

        server.close();
        if (!wm.startConfigPortal("Smarthouse")) {
          Serial.println("failed to connect and hit timeout");
          delay(3000);
          //reset and try again, or maybe put it to deep sleep
          ESP.restart();
          delay(5000);
        }

      } else if (!buttonPressed) {
        buttonState = IDLE;
      }
      break;

    case HELD:
      if (!buttonPressed) {
        buttonState = IDLE;
      }
      break;
  }
}


void loop() {
  checkButton();

  server.handleClient();
  
  currentUpTime = millis();  
  uptimeInSeconds = (currentUpTime - startTime) / 1000;
  uptime = mytime::getCurrentUptime(uptimeInSeconds);

  
  waterSensor_ADC_value = analogRead(A0);
  isWaterDetect = isDetectWater(waterSensor_ADC_value);
  waterLvl = GetWaterLevel(waterSensor_ADC_value);

  if(isWaterDetect){
    Serial.print("WaterDetect\n");

    #ifdef IS_SERVO_USE
      if(isServoOpen)
        closeServo();
    #else
      if(isServoOpen)
        closeValve();
    #endif

    httpClient->sendDetectedMessage(waterLvl); 
  }
  delay(1000);
}
