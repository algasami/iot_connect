#include "utils.hpp"

uint32_t moisture_value;
constexpr uint32_t EPSILON = 50;

/**
 *
 * 1023 - dry
 * 1023-800 - half dry
 * 800 and below - wet
 */
void handle_moisture() {
  moisture_value = analogRead(MOISTURE_PIN);

  // discord push
  static uint32_t last_moisture = 0;
  static uint32_t last = millis();
  uint32_t now = millis();
  if (now - last < mysettings.discord_update_sec * 1000) {
    return;
  }
  last = now;
  if (abs(static_cast<int32_t>(moisture_value - last_moisture)) > EPSILON) {
    char buffer[50];
    last_moisture = moisture_value;
    sprintf(buffer, "```\nA0: %d\n```\n", moisture_value);
    send_discord("Moisture Monitor 8266 - Data Update!", buffer);
  }
}