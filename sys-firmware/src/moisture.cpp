#include "utils.hpp"

uint32_t moisture_value;

/**
 *
 * 1023 - dry
 * 1023-800 - half dry
 * 800 and below - wet
 */
void handle_moisture() {
  static uint32_t last = millis();
  uint32_t now = millis();
  if (now - last < mysettings.update_sec * 1000) {
    return;
  }
  last = now;
  moisture_value = analogRead(MOISTURE_PIN);
  Serial.println(moisture_value);
}