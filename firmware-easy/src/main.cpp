#include "utils.hpp"

Settings mysettings{.buzz_on_change = false};

void setup() {
	Serial.begin(9600);
	Serial.println("Starting...");
	init_buzzer();
	init_wifi();
}

void loop() {
	uint32_t now = millis();
	if (Web::server_created) {
		Web::server.handleClient();
	}
	handle_wifi(now);
	handle_moisture(now);
}
