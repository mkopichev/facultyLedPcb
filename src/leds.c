#include "../inc/leds.h"

void timer0Init(void) {

    TCCR0B = (1 << CS01);
    TIMSK0 = (1 << OCIE0A) | (1 << TOIE0);
}

void ledsInit(void) {

    timer0Init();
    DDRD = 0xFF;
}
