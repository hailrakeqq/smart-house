#include "httpClient.h"
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <map>
#include <ArduinoJson.h>


void httpClient::sendWaterDetectedMessageToServer(){
    StaticJsonDocument<32> doc;
    doc["timestamp"] = ""; 
    doc["message"] = "Water was detected"; 

    String json;
    serializeJson(doc, json);

    auto request = httpClient::sendJSONToAPI("http://192.168.0.15:5198/api/Home/GetMessageIfWaterWasDetected",
                                            "application/json",
                                            json);
    httpClient::printResponseLog(request);
}

std::map<int, String> httpClient::sendJSONToAPI(String apiEndpoint, String contentType, String SerializedJson)
{
    Serial.println();
    Serial.println("Serialized json:");
    Serial.println(SerializedJson);
    Serial.println();
    WiFiClient wifiClient;
    HTTPClient http;
    std::map<int, String> map;

    http.begin(wifiClient, apiEndpoint);
    http.addHeader("Content-Type", contentType);
    int httpResponseCode = http.POST(SerializedJson);

    // example output map: 
    // 200 - OK
    // 404 - NotFound
    map[httpResponseCode] = http.getString();
    http.end();
    return map;
}

void httpClient::printResponseLog(std::map<int, String> response)
{
    Serial.print("HTTP Response code: ");
    Serial.println(response.begin()->first);
    Serial.print("HTTP Response message: ");
    Serial.println(response.begin()->second);
}
