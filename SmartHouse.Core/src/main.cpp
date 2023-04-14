// #include <ESP8266WiFi.h>
// #include <ESP8266HTTPClient.h>
// #include <WiFiClient.h>

// const char* ssid = "busya";
// const char* password = "0677170801";
// const char* serverUrl = "http://localhost:5198/api/Home/";

// HTTPClient httpClient;
// WiFiClient wifiClient;

// void setup() {
//   Serial.begin(115200);

//   // Connect to Wi-Fi
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.println("Connecting to WiFi...");
//   }

//   Serial.println("Connected to WiFi");

//   // Make HTTP request to server
 
//   // httpClient.begin(wifiClient,serverUrl);
//   // int httpCode = httpClient.GET();

//   // if (httpCode > 0) {
//   //   String payload = httpClient.getString();
//   //   Serial.println(payload);
//   // } else {
//   //   Serial.println("HTTP request failed");
//   // }

//   // httpClient.end();
// }

// void loop() {
//    String data = "name=John&age=20";

//     httpClient.begin(wifiClient, serverUrl);
//     httpClient.addHeader("Content-Type", "text/plain");
//     httpClient.POST(data);
//     String content = httpClient.getString();
//     httpClient.end();

//     Serial.println(content);
//     delay(5000);
// }


// #include <ESP8266WiFi.h>
// #include <ESP8266HTTPClient.h>
// #include <WiFiClient.h>

// const char* ssid = "busya";
// const char* password = "0677170801";

// const String serverName = "http://localhost:5198/api/Home/";

// unsigned long lastTime = 0;
// unsigned long timerDelay = 10000;

// void setup() {
//   Serial.begin(115200);

//   WiFi.begin(ssid, password);
//   Serial.println("Connecting");
//   while(WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println("");
//   Serial.print("Connected to WiFi network with IP Address: ");
//   Serial.println(WiFi.localIP());
 
//   Serial.println("Timer set to 10 seconds (timerDelay variable), it will take 10 seconds before publishing the first reading.");

//   randomSeed(analogRead(0));
// }

// void loop() {
//   if ((millis() - lastTime) > timerDelay) {
//     if(WiFi.status()== WL_CONNECTED){
//       WiFiClient client;
//       HTTPClient http;
//       String body = "test";
//       http.begin(client,serverName);

//       http.addHeader("Content-Type", "text/plain");
//       int httpResponseCode = http.GET();
//       String payload = http.getString();
//       //Serial.println("http request: " + http);

//       Serial.print("HTTP Response code: ");
//       Serial.println(httpResponseCode);

//       Serial.print("Payload: ");
//       Serial.println(payload);
      
//       http.end();
//     }
//     else {
//       Serial.println("WiFi Disconnected");
//     }
//     lastTime = millis();
//   }
// }


/**
   BasicHTTPClient.ino

    Created on: 24.05.2015

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;

void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("busya", "0677170801");
}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://localhost:5198/api/Home/")) {  // HTTP


      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.println("[HTTP] Unable to connect");
    }
  }

  delay(10000);
}
