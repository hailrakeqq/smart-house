#include <ESP8266WebServer.h>

class httpServer{
    private:
        ESP8266WebServer server;

    public:
        httpServer(int port);
        void handleRequest();
};