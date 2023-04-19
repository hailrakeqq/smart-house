#include <map>
#include <Arduino.h>

class httpClient{
    public:
        static void sendWaterDetectedMessageToServer();
        static std::map<int, String> sendJSONToAPI(String apiEndpoint, String contentType, String SerializedJson);
        static void printResponseLog(std::map<int, String> response);
};