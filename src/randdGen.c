#include "../inc/randGen.h"

void randArrayInit() {

    uint16_t seed = 0;

    ADMUX = (1 << REFS0);
    ADCSRA = (1 << ADEN) | (1 << ADPS2);

    for(uint8_t i = 0; i < 16; i++) {

        ADCSRA |= (1 << ADSC);
        while(ADCSRA & (1 << ADIF)) {

            continue;
        }
        ADCSRA |= (1 << ADIF);
        seed ^= (ADC << (i & 7)) | (ADC >> (8 - (i & 7)));
        _delay_ms(1);
    }
    ADCSRA &= ~(1 << ADEN);
    srand(seed);
}

// ---------- Генератор случайных чисел с запретом повторов подряд ----------
/**
 * Генерирует массив случайных чисел от 0 до 7, где никакие два соседних не равны.
 * @param arr    указатель на массив (должен быть длиной не менее length)
 * @param length длина массива (до 64 и более)
 */

void generateRandArray(uint8_t *arr, uint8_t length) {

    if(length == 0) {

        return;
    }

    // Первый элемент можно выбрать полностью случайно
    arr[0] = rand() % 8;

    // Последующие элементы
    for(uint8_t i = 1; i < length; i++) {

        uint8_t next;
        do {

            next = rand() % 8; // пробуем случайное число
        } while(next == arr[i - 1]); // пока не совпадёт с предыдущим
        arr[i] = next;
    }
}