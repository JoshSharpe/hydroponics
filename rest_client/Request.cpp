#include "Request.h"

Request::Request(String method, String path) {
    this->method = method;
    this->path = path;

    this->setHeader();
    this->setBody();
}

void Request::setHeader()
{
    this->header = String(this->method + " " + this->path + " HTTP/1.1\r\n" +
                  "Host: " + configuration.hostName + "\r\n" +
                  "User-Agent: HydroponicESP8266\r\n" +
                  "Content-Type: application/json");
}

void Request::sendRequest(WiFiClient client) {
    client.print(this->header);
    client.println();
    client.print(this->body);
    readResponse(client);
    parseResponseCode();
}

void Request::readResponse(WiFiClient client)
{
    this->responseHeaders = "";
    while (client.connected())
    {
        String line = client.readStringUntil('\n');
        this->responseHeaders += line;
        if (line == "\r")
        {
            Serial.println("headers received");
            break;
        }
    }
    this->responseBody = client.readStringUntil('\n');
}

void Request::parseResponseCode() {
    char *token;
    char currentChar;
    char firstLine[this->responseHeaders.length];

    for(int i=0; i < this->responseHeaders.length; i++)
    {
        currentChar = this->responseHeaders[i];
        firstLine[i] = currentChar;
    }

    token = strtok(firstLine, " ");
    token = strtok(NULL, " ");

    this->statusCode = atoi(token);
    if(errno == EINVAL || errno == E2BIG || errno == EDOM || errno == ERANGE) {
        this->statusCode = 500;
    }
}

int Request::getStatusCode(){
    return this->statusCode;
}

String Request::getResponseBody(){
    return this.responseBody;
}

