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

	static uint32_t last_moisture = 0;
	if (abs(static_cast<int32_t>(moisture_value - last_moisture)) > EPSILON) {
		if (mysettings.buzz_on_change) {
			buzz(FREQ_MOISTURE, 500);
		}
		last_moisture = moisture_value;
		post_moisture(moisture_value);
	}
}