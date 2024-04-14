#include <map>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <map>
#include <string>
#include <sstream>
#include "uptime.h"

/**
 * httpClient using for send request to API
 * as serialize format I use JSON
 * can be 2 log state:
 * info 
 * critical
*/
class HttpClient{
    public:
        HttpClient(WiFiClient wifiClient, String API_URL, String userEmailAddress);
        void sendDetectedMessage(double waterLvl);
        void sendWaterState(double waterLvl);
        void sendState(double waterLvl, bool valveState, struct mytime::uptime* uptime);
        void sendValveState(bool valveState);
        void sendUptime(struct mytime::uptime* uptime);
        String getExternalIP();
    private:
        String userEmailAddress;
        String APIAddress;
        WiFiClient wifiClient;
        HTTPClient http;
};