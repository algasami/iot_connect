#pragma once

#include <Arduino.h>

#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

void init_wifi();
void init_buzzer();
void handle_music(uint32_t now);
void handle_wifi(uint32_t now);
void buzz(uint32_t, uint32_t);
void send_discord(const char *name, const char *content);

void handle_moisture(uint32_t now);

void display_number(uint32_t number);

struct Router {
    char ssid[50];
    char password[50];
};

struct Note {
    uint32_t frequency; // -1 is stop
    uint32_t length;    // 1, 2, 3
};
void play_music(Note const *music_sheet);

// ! How do we add a schema for the settings?
struct Settings {
    uint32_t discord_update_sec;
    bool buzz_on_change;
};
constexpr size_t ROUTER_SIZE = 3;
constexpr uint8_t MOISTURE_PIN = A0;

constexpr uint32_t FREQ_MOISTURE = 261;        // Middle C
constexpr uint32_t FREQ_SERVER_CREATED = 293;  // D
constexpr uint32_t FREQ_WIFI_DISCONNECT = 329; // E
constexpr uint32_t FREQ_SETTINGS_UPDATE = 349; // F

constexpr bool DEBUG_DISABLE_BUZZER = false;

extern Settings mysettings;

namespace Web {
extern ESP8266WebServer server;
extern Router routers[ROUTER_SIZE];
extern const char discord_hook[];
extern bool wifi_connected, server_created;
} // namespace Web

extern uint32_t moisture_value;