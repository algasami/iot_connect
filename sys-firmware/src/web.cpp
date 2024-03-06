#include "utils.hpp"
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>
#include <LittleFS.h>
#include <WiFiClientSecure.h>

namespace Web {
ESP8266WiFiMulti wifi_multi;
ESP8266WebServer server(80);
bool wifi_connected = false, server_created = false;
} // namespace Web

using namespace Web;

void init_wifi() {
    WiFi.mode(WIFI_STA);
    Serial.println("Begin wifi initialization");
    for (size_t i = 0; i < ROUTER_SIZE; i++) {
        wifi_multi.addAP(routers[i].ssid, routers[i].password);
    }
}

void create_server();
void clean_server();

void handle_wifi() {
    static uint32_t last = millis();
    uint32_t now = millis();
    if (now - last < 1000) {
        return;
    }
    last = now;
    if (wifi_multi.run() != WL_CONNECTED) {
        if (wifi_connected) {
            Serial.println("Wifi disconnected!");
            wifi_connected = false;
            clean_server();
        }
        return;
    }
    if (!wifi_connected) {
        wifi_connected = true;
        Serial.println("Wifi connected!");
        create_server();
        Serial.println("Server created!");
        server_created = true;
    }
}

/**
 * @brief initialize the server with the following routes:
 * 1. / - GET - returns the moisture and approved status
 * 2. /settings - POST - updates the settings
 *
 * Caveat: the settings are not validated. We will need to add a schema for it.
 */
void create_server() {
    if (LittleFS.begin()) {
        Serial.println("LittleFS mounted");
    } else {
        Serial.println("LittleFS failed to mount");
        return;
    }

    server.on("/", HTTP_GET, []() {
        Serial.println("got request");
        if (LittleFS.exists("/index.html")) {
            Serial.println("sending index.html");

            // read /index.html into a buffer
            File file = LittleFS.open("/index.html", "r");
            if (file.available()) {
                server.streamFile(file, "text/html");
            }
            file.close();
        } else {
            Serial.println("sending 404");
            server.send(404, "text/plain", "404: Not Found");
        }
    });
    server.on("/settings", HTTP_POST, []() {
        Serial.println("got settings");
        bool success = true;
        if (server.hasArg("discord_update_sec")) {
            int32_t og_update = server.arg("discord_update_sec").toInt();
            if (og_update < 0) {
                success = false;
            } else {
                mysettings.discord_update_sec = og_update;
            }
        }
        if (success) {
            server.send(201, "text/html",
                        "<!DOCTYPE html><html><head><title>MM Update "
                        "Success</title></head><body><h1>Success!</h1><button "
                        "onclick=\"window.history.back()\">Go "
                        "Back</button></body></html>");
        } else {
            server.send(400, "text/html",
                        "<!DOCTYPE html><html><head><title>MM Update "
                        "Failure</title></head><body><h1>Failure!</h1><button "
                        "onclick=\"window.history.back()\">Go "
                        "Back</button></body></html>");
        }
    });

    server.on("/status", HTTP_GET, []() {
        char buffer[50];
        JsonDocument data;
        data["moisture"] = moisture_value;
        data["free_heap"] = ESP.getFreeHeap();
        serializeJson(data, buffer);
        server.send(200, "application/json", buffer);
    });

    server.begin();

    {
        char buffer[100];
        sprintf(buffer,
                "Moisture Monitor Online!\n```\nSSID:%s\nLOIP:%s\n```\n",
                WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
        send_discord("Moisture Monitor 8266 - system", buffer);
    }
}

void clean_server() {
    server.close();
    LittleFS.end();
}

WiFiClientSecure sec_client;
HTTPClient http;
void send_discord(const char *name, const char *content) {
    char buffer[500];
    JsonDocument data;
    data["username"] = name;
    data["content"] = content;
    serializeJsonPretty(data, buffer);
    sec_client.setInsecure();
    http.begin(sec_client, discord_hook);

    http.addHeader("Content-Type", "application/json");
    http.POST(buffer);

    http.end();
}