#include "utils.hpp"

Settings mysettings{.update_on_change = false, .update_sec = 30};

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
}
