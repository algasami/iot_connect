#include "utils.hpp"

Settings mysettings;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.begin(9600);
  init_wifi();
}

void loop() {
  if (Web::server_created) {
    Web::server.handleClient();
  }
  handle_wifi();
}
