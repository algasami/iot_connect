#include "utils.hpp"

constexpr uint8_t BUZZER_PIN = D0;

namespace Tones {
constexpr uint32_t C3 = 131, D3 = 147, E3 = 165, F3 = 175, G3 = 196, A3 = 220, B3 = 247;
constexpr uint32_t C4 = 262, D4 = 294, E4 = 330, F4 = 349, G4 = 392, A4 = 440, B4 = 494;
constexpr uint32_t C5 = 523, D5 = 587, E5 = 659, F5 = 698, G5 = 784, A5 = 880, B5 = 988;
} // namespace Tones

Note const LITTLE_STAR[] = {{Tones::C4, 4}, {Tones::C4, 4}, {Tones::G4, 4}, {Tones::G4, 4},
                            {Tones::A4, 4}, {Tones::A4, 4}, {Tones::G4, 8}, {Tones::F4, 4},
                            {Tones::F4, 4}, {Tones::E4, 4}, {Tones::E4, 4}, {Tones::D4, 4},
                            {Tones::D4, 4}, {Tones::C4, 8}, {-1, 0}};

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
}

void handle_music(uint32_t now) {
    static uint32_t last = 0;
    if (!playing)
        return;

    if (current_index != 0 && now - last < (sheet + current_index - 1)->length * 100) {
        return;
    }

    Note const *const current_note = sheet + current_index;
    if (current_note->frequency < 0) {
        // end of file
        playing = false;
        sheet = nullptr;
        return;
    }

    last = now;
    buzz(current_note->frequency, current_note->length * 100);
    current_index++;
}