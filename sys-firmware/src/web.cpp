#include "utils.hpp"
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

namespace Web {
ESP8266WiFiMulti wifi_multi;
ESP8266WebServer server(80);
bool wifi_connected = false, server_created = false;
} // namespace Web

using namespace Web;

void init_wifi() {
  Serial.println("Begin wifi initialization");
  for (size_t i = 0; i < ROUTER_SIZE; i++) {
    wifi_multi.addAP(routers[i].ssid, routers[i].password);
  }
}

void create_server();
void clean_server();
void send_discord(const char *name, const char *content);

void handle_wifi() {
  if (wifi_multi.run() != WL_CONNECTED) {
    if (wifi_connected) {
      wifi_connected = false;
      clean_server();
    }
    return;
  }
  if (!wifi_connected) {
    wifi_connected = true;
    Serial.println("Wifi connected!");
    create_server();
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
  server.begin();
  server.on("/", HTTP_GET, []() {
    char buffer[200];
    JsonDocument res;
    res["moisture"] = 1.0;
    res["approved"] = true;
    serializeJson(res, buffer);
    server.send(200, "application/json", buffer);
  });
  server.on("/settings", HTTP_POST, []() {
    // ! ugly code (I NEED TO FIX THIS!!! maybe via SCHEMA)
    if (server.hasArg("update_sec")) {
      mysettings.update_sec = server.arg("update_sec").toInt();
    }
    if (server.hasArg("update_on_change")) {
      mysettings.update_on_change =
          strcmp(server.arg("update_on_change").c_str(), "true") ? false : true;
    }
    server.send(201, "text/plain", "success");
  });
  {
    char msg_buffer[100];
    sprintf(msg_buffer,
            "Moisture Monitor Online!\n```\nSSID:%s\nLOIP:%s\n```\n",
            WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
    send_discord("Moisture Monitor 8266 - system", msg_buffer);
  }
}

void clean_server() { server.close(); }

WiFiClientSecure sec_client;
HTTPClient http;
void send_discord(const char *name, const char *content) {
  char send_buffer[200];
  JsonDocument data;
  data["username"] = name;
  data["content"] = content;
  serializeJsonPretty(data, send_buffer);
  sec_client.setInsecure();
  http.begin(sec_client, discord_hook);

  http.addHeader("Content-Type", "application/json");
  http.POST(send_buffer);

  http.end();
}