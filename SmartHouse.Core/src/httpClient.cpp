#include "../include/httpClient.h"


HttpClient::HttpClient(WiFiClient wifiClient, String APIAddress, String userEmailAddress) : 
    wifiClient(wifiClient),
    APIAddress(APIAddress),
    userEmailAddress(userEmailAddress) {}


void HttpClient::sendDetectedMessage(double waterLvl) {
    std::stringstream ss;
    ss << "Water was detected - " << waterLvl;
    std::string message = ss.str();

  
    StaticJsonDocument<128> doc;
    doc["timestamp"] = "";
    doc["logLevel"] = "Critical";
    doc["userEmail"] = userEmailAddress;
    doc["message"] = message;

    String json;
    serializeJson(doc, json);
    http.begin(wifiClient, APIAddress);
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(json);
    //TODO: add request handler
}

void HttpClient::sendValveState(bool valveState){
    StaticJsonDocument<128> doc;
    doc["timestamp"] = "";
    doc["logLevel"] = "Info";
    doc["userEmail"] = userEmailAddress;
    doc["valveState"] = valveState;

    String json;
    serializeJson(doc, json);
    http.begin(wifiClient, APIAddress);
    http.addHeader("Content-Type", "application/json");
    // int httpResponseCode = http.POST(json);
    http.POST(json);
}

void HttpClient::sendState(double waterLvl, bool valveState, struct mytime::uptime* uptime){
    StaticJsonDocument<128> doc;
    doc["timestamp"] = "";
    doc["logLevel"] = "Info";
    doc["userEmail"] = userEmailAddress;
    doc["valveState"] = valveState;
    doc["waterLevel"] = waterLvl;
    doc["days"] = uptime->days;
    doc["hours"] = uptime->hours;
    doc["minutes"] = uptime->minutes;
    doc["seconds"] = uptime->seconds;
    doc["uptime"] = uptime->uptimeStr;

    String json;
    serializeJson(doc, json);
    http.begin(wifiClient, APIAddress);
    http.addHeader("Content-Type", "application/json");
    // int httpResponseCode = http.POST(json);
    http.POST(json);
}

void HttpClient::sendUptime(struct mytime::uptime* uptime){
    StaticJsonDocument<128> doc;
    doc["timestamp"] = "";
    doc["logLevel"] = "Info";
    doc["userEmail"] = userEmailAddress;
    doc["days"] = uptime->days;
    doc["hours"] = uptime->hours;
    doc["minutes"] = uptime->minutes;
    doc["seconds"] = uptime->seconds;
    doc["uptime"] = uptime->uptimeStr;
   
    String json;
    serializeJson(doc, json);
    http.begin(wifiClient, APIAddress);
    http.addHeader("Content-Type", "application/json");
    // int httpResponseCode = http.POST(json); 
    http.POST(json);
}

String HttpClient::getExternalIP() {
  http.begin(wifiClient, "http://httpbin.org/ip");

  int httpCode = http.GET();

  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      int start = payload.indexOf("\"origin\": \"") + 11; // 11 is the length of "\"origin\": \""
      int end = payload.indexOf("\"", start);
      return payload.substring(start, end);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  return "";
}