#pragma once

#include <Arduino.h>

#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

void init_wifi();
void handle_wifi();
void send_discord(const char *name, const char *content);

void handle_moisture();

struct Router {
  char ssid[50];
  char password[50];
};

// ! How do we add a schema for the settings?
struct Settings {
  uint32_t discord_update_sec = 30;
};
constexpr size_t ROUTER_SIZE = 2;
constexpr uint8_t MOISTURE_PIN = A0;

extern Settings mysettings;

namespace Web {
extern ESP8266WiFiMulti wifi_multi;
extern Router routers[ROUTER_SIZE];
extern ESP8266WebServer server;
extern const char discord_hook[];
extern bool wifi_connected, server_created;
} // namespace Web

extern uint32_t moisture_value;