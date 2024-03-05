#include "utils.hpp"

Settings mysettings{.update_sec = 5, .update_on_change = false};

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
