#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <map>

class httpClient{
    public:
        static void sendWaterDetectedMessageToServer();
        static std::map<int, String> sendJSONToAPI(String apiEndpoint, String contentType, String SerializedJson);
        static void printResponseLog(std::map<int, String> response);
};