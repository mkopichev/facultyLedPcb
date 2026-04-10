#include "../inc/leds.h"

void timer2Init(void) {

    TCCR2 = (1 << CS22);
    TIMSK = (1 << OCIE2) | (1 << TOIE2);
}

void ledsInit(void) {

    timer2Init();
    DDRD = 0xFF;
}
