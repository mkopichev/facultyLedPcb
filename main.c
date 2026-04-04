#include "inc/common.h"

int8_t ledNumber = -1;
uint8_t ledsQuantity = 1;
uint8_t randomArrayFirst[64];
uint8_t randomArraySecond[64];

int main(void) {

    ledsInit();
    sei();

    // Инициализация ГСЧ при старте
    randArrayInit();
    generateRandArray(randomArrayFirst, 64);
    for(uint16_t i = 0; i < 1000; i++) {

        rand();
    }
    generateRandArray(randomArraySecond, 64);

    while(1) {

        _NOP();
    }
}

ISR(TIMER0_OVF_vect) {

    static int16_t i = 0;
    static uint8_t j = 0;
    static bool dir = true;

    if(dir) {

        i+=2;
        if(i >= 255) {

            i = 255;
            dir = false;
        }
    } else {

        i-=2;
        if(i <= 0) {

            i = 0;
            dir = true;
            if(++j >= sizeof(randomArrayFirst)) {

                j = 0;
            }
            if(randomArrayFirst[j] % randomArraySecond[j]) {

                ledsQuantity = 3;
            } else if(randomArraySecond[j] % randomArrayFirst[j]) {

                ledsQuantity = 2;
            } else {

                ledsQuantity = 1;
            }
            ledNumber = randomArrayFirst[j];
        }
    }

    OCR0A = i;

    switch(ledsQuantity) {
    case 1: {

        PORTD |= (1 << ledNumber);
        break;
    }
    case 2: {

        PORTD |= (1 << ledNumber) | (1 << randomArrayFirst[ledNumber]);
        break;
    }
    case 3:

        PORTD |= (1 << ledNumber) | (1 << randomArrayFirst[ledNumber]) | (1 << randomArraySecond[ledNumber]);
        break;
    }
}

ISR(TIMER0_COMPA_vect) {

    PORTD = 0;
}
