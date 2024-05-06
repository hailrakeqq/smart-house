#include "../include/httpClient.h"


HttpClient::HttpClient(WiFiClient wifiClient, String APIAddress, String userEmailAddress, IPAddress localIP) : 
    wifiClient(wifiClient),
    APIAddress(APIAddress),
    userEmailAddress(userEmailAddress),
    localIP(localIP) {}


void HttpClient::sendDetectedMessage(double waterLvl) {
    std::stringstream ss;
    ss << "Water was detected - " << waterLvl << " cm";
    std::string message = ss.str();

    StaticJsonDocument<256> doc;
    doc["timestamp"] = "";
    doc["logLevel"] = "Critical";
    doc["userEmail"] = userEmailAddress;
    doc["message"] = message;
    doc["localIP"] = localIP;
    doc["externalIP"] = externalIP;

    String json;
    serializeJson(doc, json);
       
    http.begin(wifiClient, APIAddress + "/api/Main/waterdetect");
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(json);
    Serial.print(httpResponseCode);
    Serial.print('\n');
}

void HttpClient::sendDeviceIPToAPI(String localIP, String externalIP, String userEmail){
    StaticJsonDocument<256> doc;
    doc["internalIP"] = localIP;
    doc["externalIP"] = externalIP;
    doc["userEmail"] = userEmail;

    String json;
    serializeJson(doc,json);

    http.begin(wifiClient, APIAddress + "/api/Main/senddeviceip");
    http.addHeader("Content-Type", "application/json");
    int respone = http.POST(json);
    Serial.println(respone);
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
    StaticJsonDocument<512> doc;
    doc["logLevel"] = "Info";
    doc["userEmail"] = userEmailAddress;
    doc["valveState"] = valveState;
    doc["waterLevel"] = waterLvl;
    doc["days"] = uptime->days;
    doc["hours"] = uptime->hours;
    doc["minutes"] = uptime->minutes;
    doc["seconds"] = uptime->seconds;
    doc["uptime"] = uptime->uptimeStr;
    doc["pingResult"] = "";
    doc["localIP"] = localIP;
    doc["externalIP"] = externalIP;
    
    String json;
    serializeJson(doc, json);
    // Serial.print(json);
    // Serial.print('\n');

    http.begin(wifiClient, APIAddress);
    http.addHeader("Content-Type", "application/json");
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

void HttpClient::setExternalIP(String externalIP){
  this->externalIP = externalIP;
}

String HttpClient::getExternalIP() {
  http.begin(wifiClient, "http://httpbin.org/ip");

  int httpCode = http.GET();

  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      int start = payload.indexOf("\"origin\": \"") + 11;
      int end = payload.indexOf("\"", start);
      String result = payload.substring(start, end);
      return result;
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  return "";
}