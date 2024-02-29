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

// ! How do we add a schema for the settings?
struct Settings {
  uint32_t update_sec = 30;
  bool update_on_change = false;
};
constexpr size_t ROUTER_SIZE = 2;

extern Settings mysettings;

namespace Web {
extern ESP8266WiFiMulti wifi_multi;
extern Router routers[ROUTER_SIZE];
extern ESP8266WebServer server;
extern const char discord_hook[];
extern bool wifi_connected, server_created;
} // namespace Web

inline const char *get_SSID() { return WiFi.SSID().c_str(); }
inline const char *get_local_IP() { return WiFi.localIP().toString().c_str(); }