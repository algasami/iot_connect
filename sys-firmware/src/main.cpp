#include "utils.hpp"

Settings mysettings{.discord_update_sec = 5};

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
}
