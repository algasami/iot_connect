#include "utils.hpp"

Settings mysettings{.discord_update_sec = 2};

void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");
  init_wifi();
}

void loop() {

  if (Web::server_created) {
    Web::server.handleClient();
  }

  handle_wifi();
  handle_moisture();

  static uint32_t last = millis();
  uint32_t now = millis();
  if (now - last < 1000) {
    return;
  } else {
    last = now;
    Serial.printf("Free heap: %d\n", ESP.getFreeHeap());
  }
}
