#include "keypad.h"

static const uint8 keypad_val[KEYPAD_ROWS][KEYPAD_COLS] = {
   {'1', '2', '3', '-'},
   {'4', '5', '6', '*'},
   {'7', '8', '9', '/'},
   {'#', '0', '=', '+'}
};
#if ENABLE_KEYPAD_APIS == ENABLE_KEYPAD

Err_check_t keypad_init(keypad_t *keypad) {
    Err_check_t e_check = OK;
    uint8 count = 0;
    if (NULL == keypad) {
        e_check = N_OK;
    } else {
        for (count = 0; count < KEYPAD_ROWS; count++)
            e_check &= gpioPinInit(&(keypad->keypad_rows[count]));
        for (count = 0; count < KEYPAD_COLS; count++)
            e_check &= gpioPinInit(&(keypad->keypad_cols[count]));
    }
    return e_check;
}
#endif

#if ENABLE_KEYPAD_APIS == ENABLE_KEYPAD

Err_check_t keypad_get_value(keypad_t *keypad, uint8 *value) {
    Err_check_t e_check = OK;
    pinState_t state;
    uint8 count;
    if (NULL == keypad || NULL == value) {
        e_check = N_OK;
    } else {
        while (1) {
            for (uint8 row = 0; row < KEYPAD_ROWS; row++) {
                for (count = 0; count < KEYPAD_ROWS; count++) {
                    e_check &= e_check &= gpioSetPinState(&(keypad->keypad_rows[count]), LOW);
                }
                e_check &= gpioSetPinState(&(keypad->keypad_rows[row]), HIGH);
                for (uint8 col = 0; col < KEYPAD_COLS; col++) {
                    e_check &= gpioGetPinSate(&(keypad->keypad_cols[col]), &state);
                    if (HIGH == state) {
                        *value = keypad_val[row][col];
                        return e_check;
                    }
                }
                e_check &= gpioSetPinState(&(keypad->keypad_rows[row]), LOW);
            }
        }
    }
    return e_check;
}
#endif
