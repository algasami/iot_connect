#include "utils.hpp"

Settings mysettings{.buzz_on_change = false};

void setup() {
	// 設定baud速率
	Serial.begin(9600);
	Serial.println("Starting...");
	init_buzzer();
	init_wifi();
}

void loop() {
	uint32_t now = millis();
	// WiFi 掃描
	handle_wifi(now);
	// 濕度感測
	handle_moisture(now);
}
