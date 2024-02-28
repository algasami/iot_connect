#include "utils.hpp"
#include <ESP8266HTTPClient.h>

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

void handle_wifi() {
  static uint32_t last = millis();
  uint32_t now = millis();
  if (now - last > 1000) {
    last = now;
  } else {
    return;
  }
  if (wifi_multi.run() != WL_CONNECTED) {
    if (wifi_connected) {
      wifi_connected = false;
      clean_server();
    }
    return;
  }
  if (!wifi_connected) {
    wifi_connected = true;
    create_server();
    server_created = true;
  }
}

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
      const char *str = server.arg("update_on_change").c_str();
      mysettings.update_on_change =
          strcmp(server.arg("update_on_change").c_str(), "true") ? false : true;
    }
    server.send(201, "text/plain", "success");
  });
  {
    char msg_buffer[100];
    sprintf(msg_buffer,
            "Moisture Monitor Online!\n```\nSSID:%s\nLOIP:%s\n```\n",
            get_SSID(), get_local_IP());
    send_discord("Moisture Monitor 8266 - system", msg_buffer);
  }
}

void clean_server() { server.close(); }

HTTPClient client;
void send_discord(const char *name, const char *content) {
  char send_buffer[200];
  JsonDocument data;
  data["username"] = name;
  data["content"] = content;
  serializeJson(data, send_buffer);
  client.begin(discord_hook);
  client.addHeader("Content-Type", "application/json");
  client.POST(send_buffer);
  client.end();
}