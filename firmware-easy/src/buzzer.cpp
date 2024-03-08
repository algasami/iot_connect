#include "utils.hpp"

constexpr uint8_t BUZZER_PIN = D0;

void init_buzzer() { pinMode(BUZZER_PIN, OUTPUT); }
void buzz(uint32_t freq, uint32_t duration_ms) {
	if (DEBUG_DISABLE_BUZZER)
		return;
	tone(BUZZER_PIN, freq, duration_ms);
}
