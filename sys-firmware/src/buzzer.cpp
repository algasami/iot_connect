#include "utils.hpp"

constexpr uint8_t BUZZER_PIN = D0;

bool should_buzz = false;
inline void init_buzzer() {
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);
}
inline void buzz() { should_buzz = true; }

void handle_buzzer(uint32_t now) {
    static uint32_t last = millis();
    static bool buzzer_state = false;
    if (now - last < 1000) {
        return;
    }
    last = now;
    if (should_buzz) {
        if (!buzzer_state) {
            buzzer_state = true;
            digitalWrite(BUZZER_PIN, HIGH);
        }
    } else {
        if (buzzer_state) {
            buzzer_state = false;
            digitalWrite(BUZZER_PIN, LOW);
        }
    }
}