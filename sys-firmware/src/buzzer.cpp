#include "sheets.hpp"
#include "utils.hpp"

constexpr uint8_t BUZZER_PIN = D0;

void init_buzzer() { pinMode(BUZZER_PIN, OUTPUT); }
void buzz(uint32_t freq, uint32_t duration_ms) {
    if (DEBUG_DISABLE_BUZZER)
        return;
    tone(BUZZER_PIN, freq, duration_ms);
}

bool playing = false;
uint32_t current_index = 0;
Note const *sheet;

void play_music(Note const *music_sheet) {
    sheet = music_sheet;
    playing = true;
    current_index = 0;
}

void handle_music(uint32_t now) {
    static uint32_t last = 0;
    if (!playing)
        return;

    if (current_index != 0 && now - last < (sheet + current_index - 1)->length * 100 + 10) {
        // 10 ms delay for visible separation (sounds more natural)
        return;
    }
    Serial.println(current_index);

    Note const *const current_note = sheet + current_index;

    if (current_note->frequency == 0) {
        noTone(BUZZER_PIN);
    } else if (current_note->frequency < 0) {
        playing = false;
        sheet = nullptr;
        return;
    } else {
        buzz(static_cast<uint32_t>(current_note->frequency), current_note->length * 100);
    }

    last = now;
    current_index++;
}