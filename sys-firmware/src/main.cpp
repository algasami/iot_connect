#include "utils.hpp"

Settings mysettings;

void setup() {
  LEDs::setup_leds();
  Serial.begin(9600);
  init_wifi();
}

void loop() {
  if (Web::server_created) {
    Web::server.handleClient();
  }
  handle_wifi();
  LEDs::handle_leds(); // handles traffic light
}
