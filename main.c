#include "inc/common.h"

int8_t ledNumber = -1;
uint8_t ledsQuantity = 1;
uint8_t randomArrayFirst[8];
uint8_t randomArraySecond[8];

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

        for(uint8_t i = 0; i < sizeof(randomArrayFirst); i++) {

            if(randomArrayFirst[i] % randomArraySecond[i]) {

                ledsQuantity = 3;
            } else if(randomArraySecond[i] % randomArrayFirst[i]) {

                ledsQuantity = 2;
            } else {

                ledsQuantity = 1;
            }

            ledNumber = randomArrayFirst[i];

            for(float i = 0; i < 255; i += 0.051) {

                OCR0A = ((uint8_t)i);
                DELAY_TIME;
            }

            TCCR0B &= ~(1 << CS01);
            for(uint16_t i = 0; i < 25000; i++) {

                DELAY_TIME;
            }
            TCCR0B |= (1 << CS01);

            for(float i = 0; i < 255; i += 0.051) {

                OCR0A = 255 - ((uint8_t)i);
                DELAY_TIME;
            }
            TCCR0B &= ~(1 << CS01);
            for(uint16_t i = 0; i < 25000; i++) {

                DELAY_TIME;
            }
            TCCR0B |= (1 << CS01);
        }
    }
}

ISR(TIMER0_COMPA_vect) {

    switch(ledsQuantity) {
    case 1: {

        PORTD &= ~(1 << ledNumber);
        break;
    }
    case 2: {

        PORTD &= ~((1 << ledNumber) | (1 << randomArrayFirst[ledNumber]));
        break;
    }
    case 3:
        PORTD &= ~((1 << ledNumber) | (1 << randomArrayFirst[ledNumber]) | (1 << randomArraySecond[ledNumber]));
        break;
    }
}

ISR(TIMER0_OVF_vect) {

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