#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include <string>

#ifndef config_h
#define config_h
#include "config.h"
#endif

#ifndef request_h
#define request_h
#include "Request.h"
#endif

#ifndef switch_request_h
#define switch_request_h
#include "SwitchRequest.h"
#endif

const String SwitchLogPath = "/api/plants/logs/switch";
const String TemperatureLogPath = "/api/plants/logs/temperature";

const char* SwitchCommand = "switch";
const char* LightsCommand = "lights";
const char* WaterCommand = "water";
const char* OnCommand = "on";
const char* OffCommandd = "off";

const bool DebugMode = true;

void setup()
{
    initHardware();
    setupWifi();
}

void loop()
{
    if(Serial.available() > 0) {
        String command = Serial.readString();
        Request *r = parseCommand(command);
        WiFiClient client = buildClient();
        if(!client.connected()) {
            Serial.println(500);
            return;
        }
        r->sendRequest(client);
        int statusCode = r->getStatusCode();
        Serial.println(statusCode);
    }
}

void initHardware()
{
    Serial.begin(115200);
}

void setupWifi()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(configuration.wifiUsername, configuration.wifiPassword);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        if (DebugMode)
        {
            Serial.print(".");
        }
    }

    if (DebugMode)
    {
        Serial.println("");
        Serial.println("WiFi connected");
    }
}

Request * parseCommand(String cmd) {
    char *firstCommand;
    char currentChar;
    char charCommand[cmd.length()];

    for(int i=0; i < cmd.length(); i++)
    {
        currentChar = cmd[i];
        charCommand[i] = currentChar;
    }

    firstCommand = strtok(charCommand, " ");
    if (strcmp(firstCommand, SwitchCommand) == 0)
    {
        char *secondCommand = strtok(NULL, " ");
        char *thirdCommand = strtok(NULL, " ");

        if(strcmp(secondCommand, LightsCommand) == 0 && strcmp(thirdCommand, OnCommand)) {
            return new SwitchRequest("POST", SwitchType::Lights, true);
        } else if(strcmp(secondCommand, LightsCommand) == 0 && strcmp(thirdCommand, OffCommandd)) {
            return new SwitchRequest("POST", SwitchType::Lights, false);
        } else if(strcmp(secondCommand, WaterCommand) == 0 && strcmp(thirdCommand, OnCommand)) {
            return new SwitchRequest("POST", SwitchType::WaterPump, true);
        } else if(strcmp(secondCommand, WaterCommand) == 0 && strcmp(thirdCommand, OffCommandd)) {
            return new SwitchRequest("POST", SwitchType::WaterPump, false);
        }
    }
    
    return new SwitchRequest("POST", SwitchType::WaterPump, false);
}

WiFiClient buildClient()
{
    if (DebugMode)
    {
        // Print data.
        Serial.print("connecting to ");
        Serial.print(configuration.hostName);
        Serial.print(':');
        Serial.println(configuration.port);
    }

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    int iter = 0;

    while (!client.connect(configuration.hostName, configuration.port) && iter < 10)
    {
        delay(5000);
        iter++;
    }

    return client;
}