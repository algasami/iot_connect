#include "utils.hpp"

uint32_t moisture_value;
constexpr uint32_t EPSILON = 30;

/**
 *
 * 1023 - dry
 * 1023-800 - half dry
 * 800 and below - wet
 */
void handle_moisture(uint32_t now) {
    static uint32_t base_last = millis();
    if (now - base_last < 200) {
        return;
    }
    base_last = now;
    moisture_value = analogRead(MOISTURE_PIN);
    display_number(moisture_value);

    // discord push
    static uint32_t last_moisture = 0;
    static uint32_t last = millis();
    if (now - last < mysettings.discord_update_sec * 1000) {
        return;
    }
    last = now;
    if (abs(static_cast<int32_t>(moisture_value - last_moisture)) > EPSILON) {
        if (mysettings.buzz_on_change) {
            buzz(FREQ_MOISTURE, 500);
        }
        char buffer[50];
        last_moisture = moisture_value;
        sprintf(buffer, "```\nA0: %d\n```\n", moisture_value);
        send_discord("Moisture Monitor 8266 - Data Update!", buffer);
    }
}