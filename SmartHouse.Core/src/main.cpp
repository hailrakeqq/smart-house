#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "busya";
const char* password = "0677170801";
const char* serverUrl = "http://localhost:5198/api/Home?param1=value1&param2=value2";

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  // Make HTTP request to server
  HTTPClient http;
  WiFiClient client;
  http.begin(client,serverUrl);
  int httpCode = http.GET();

  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println(payload);
  } else {
    Serial.println("HTTP request failed");
  }

  http.end();
}

void loop() {
  // Nothing to do here
}