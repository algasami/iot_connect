#include <Arduino.h>
#include <cstdint>

struct Note {
    int32_t frequency; // -1 is stop, 0 is silence
    uint32_t length;   // 1, 2, 3
};

namespace Tones {
constexpr uint32_t C3 = 131, D3 = 147, E3 = 165, F3 = 175, G3 = 196, A3 = 220, B3 = 247;
constexpr uint32_t C4 = 262, D4 = 294, E4 = 330, F4 = 349, G4 = 392, A4 = 440, B4 = 494;
constexpr uint32_t C5 = 523, D5 = 587, E5 = 659, F5 = 698, G5 = 784, A5 = 880, B5 = 988;
constexpr uint32_t Cb3 = 123, Db3 = 139, Fb3 = 185, Gb3 = 185, Ab3 = 208, Bb3 = 233;
constexpr uint32_t Cb4 = 247, Db4 = 277, Fb4 = 370, Gb4 = 370, Ab4 = 415, Bb4 = 466;
constexpr uint32_t Cb5 = 494, Db5 = 554, Fb5 = 740, Gb5 = 740, Ab5 = 830, Bb5 = 932;
} // namespace Tones

Note const PROGMEM LITTLE_STAR[] = {{Tones::C4, 4}, {Tones::C4, 4}, {Tones::G4, 4}, {Tones::G4, 4},
                                    {Tones::A4, 4}, {Tones::A4, 4}, {Tones::G4, 8}, {Tones::F4, 4},
                                    {Tones::F4, 4}, {Tones::E4, 4}, {Tones::E4, 4}, {Tones::D4, 4},
                                    {Tones::D4, 4}, {Tones::C4, 8}, {-1, 0}};
// popular sheets
// mario
Note const PROGMEM MARIO[] = {
    {Tones::E5, 8}, {Tones::E5, 8}, {Tones::E5, 8},  {Tones::C5, 8}, {Tones::E5, 8},
    {Tones::G5, 8}, {Tones::G4, 8}, {Tones::C5, 8},  {Tones::G4, 8}, {Tones::E4, 8},
    {Tones::A4, 8}, {Tones::B4, 8}, {Tones::Bb4, 8}, {Tones::A4, 8}, {Tones::G4, 8},
    {Tones::E5, 8}, {Tones::G5, 8}, {Tones::A5, 8},  {Tones::F5, 8}, {Tones::G5, 8},
    {Tones::E5, 8}, {Tones::C5, 8}, {Tones::D5, 8},  {Tones::B4, 8}, {Tones::C5, 8},
    {Tones::G4, 8}, {Tones::E4, 8}, {Tones::A4, 8},  {Tones::B4, 8}, {Tones::Bb4, 8},
    {Tones::A4, 8}, {Tones::G4, 8}, {Tones::E5, 8},  {Tones::G5, 8}, {Tones::A5, 8},
    {Tones::F5, 8}, {Tones::G5, 8}, {Tones::E5, 8},  {Tones::C5, 8}, {Tones::D5, 8},
    {Tones::B4, 8}, {Tones::C5, 8}, {Tones::G4, 8},  {Tones::E4, 8}, {Tones::E5, 8},
    {Tones::E5, 8}, {Tones::E5, 8}, {Tones::C5, 8},  {-1, 0}};