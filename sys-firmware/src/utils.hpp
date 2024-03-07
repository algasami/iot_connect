#pragma once

#include <Arduino.h>

#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

void init_wifi();
inline void init_buzzer();
void handle_wifi(uint32_t now);
void handle_buzzer(uint32_t now);
inline void buzz();
void send_discord(const char *name, const char *content);

void handle_moisture(uint32_t now);

void display_number(uint32_t number);

struct Router {
    char ssid[50];
    char password[50];
};

// ! How do we add a schema for the settings?
struct Settings {
    uint32_t discord_update_sec = 30;
};
constexpr size_t ROUTER_SIZE = 3;
constexpr uint8_t MOISTURE_PIN = A0;

extern Settings mysettings;

namespace Web {
extern ESP8266WebServer server;
extern Router routers[ROUTER_SIZE];
extern const char discord_hook[];
extern bool wifi_connected, server_created;
} // namespace Web

extern uint32_t moisture_value;