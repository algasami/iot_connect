#include "utils.hpp"
using namespace LEDs;

inline void led_on(const uint8_t pin) { digitalWrite(pin, LOW); }
inline void led_off(const uint8_t pin) { digitalWrite(pin, HIGH); }

void LEDs::setup_leds() {
  pinMode(RED_OUT, OUTPUT);
  pinMode(YELLOW_OUT, OUTPUT);
  pinMode(GREEN_OUT, OUTPUT);

  led_off(RED_OUT);
  led_off(YELLOW_OUT);
  led_off(GREEN_OUT);
}

/**
 * @brief handle the leds
 * This mimics a traffic light
 * Timestamp visualization:
 * 0 - 1000: red
 * 1000 - 1500: yellow
 * 1500 - 3500: green
 * total: 3500 (ms)
 */
void LEDs::handle_leds() {
  static uint32_t last = millis();
  constexpr uint32_t red_interval = 1000;
  constexpr uint32_t yellow_interval = 500;
  constexpr uint32_t green_interval = 2000;
  uint32_t now = millis();
  if (now - last > red_interval + yellow_interval + green_interval) {
    last = now;
  }
  if (now - last <= red_interval) {
    last = now;
    led_on(RED_OUT);
    led_off(YELLOW_OUT);
    led_off(GREEN_OUT);
  } else if (now - last > red_interval &&
             now - last <= red_interval + yellow_interval) {
    led_off(RED_OUT);
    led_on(YELLOW_OUT);
    led_off(GREEN_OUT);
  } else {
    led_off(RED_OUT);
    led_off(YELLOW_OUT);
    led_on(GREEN_OUT);
  }
}