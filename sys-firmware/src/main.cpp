#include "utils.hpp"

Settings mysettings{.discord_update_sec = 2};

void setup() {
    Serial.begin(9600);
    Serial.println("Starting...");
    init_buzzer();
    init_wifi();
}

void loop() {
    if (Web::server_created) {
        Web::server.handleClient();
    }

    uint32_t now = millis();
    handle_wifi(now);
    handle_moisture(now);
    handle_buzzer(now);
}
