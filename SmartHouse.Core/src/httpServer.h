#include "include.h"

class httpServer{
    private:
        ESP8266WebServer server(4000);

    public:
        void handleRequest();
};