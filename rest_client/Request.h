#include <WString.h>
#include <ESP8266WiFi.h>
#include "RequestType.h"

#ifndef config_h
#define config_h
#include "config.h"
#endif

class Request {
    private:
        void readResponse(WiFiClient client);
        void parseResponseCode();

    protected:
        String method;
        String path;
        String header;
        String body = "";
        String responseHeaders;
        int statusCode;
        String responseBody;

        void setHeader();
        virtual void setBody () =0;

    public:
        Request(String method, String path);
        void sendRequest(WiFiClient client);

        int getStatusCode();
        String getResponseBody();
};
