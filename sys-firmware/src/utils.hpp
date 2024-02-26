#pragma once

#include <Arduino.h>

#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

void init_wifi();
void handle_wifi();

struct Router {
  char ssid[50];
  char password[50];
};
constexpr size_t ROUTER_SIZE = 2;

namespace Web {
extern ESP8266WiFiMulti wifi_multi;
extern Router routers[ROUTER_SIZE];
extern ESP8266WebServer server;
extern bool wifi_connected, server_created;
} // namespace Web