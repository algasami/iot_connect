#include "utils.hpp"

#include <TM1637Display.h>

void display_number(uint32_t number) {
    // The display is connected to the following pins:
    // CLK -> D5
    // DIO -> D6
    TM1637Display display(D1, D2);
    display.setBrightness(0x0a);
    display.showNumberDec(number, true);
}
