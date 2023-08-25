#ifndef _STOP_WATCH_
#define _STOP_WATCH_
#include "std_lib.h"
#include "std_types.h"
#include "TM4C123GH6PM.h"
#include "HAL/LCD/lcd.h"
#include "HAL/LED/led.h"
#include "MCAL/GPIO/gpio.h"
#include "HAL/KEYPAD/keypad.h"
#include "MCAL/SYSTICK/systick.h"
#include "HAL/BUTTON/button.h"

void Counter(void);

volatile uint32 count = 0;
uint8 secs, hours, mins;
uint8 startFlag = 0, stopFlag = 0;
buttonState_t startButtonState, stopButtonState;

led_t led1 = {
    .pin = GPIO_PIN1,
    .port = PORTF,
    .state = LED_OFF};

pinConfig_t RW = {.port = PORTE,
                  .pin = GPIO_PIN3,
                  .direction = OUTPUT,
                  .mode = DIO,
                  .pinAttach = NO_ATTACH,
                  .state = LOW,
                  .pinOutCurrent = PIN_CURRENT_2mA};

lcd_t lcd1 = {
    .lcd_connection = _4_BIT,

    .lcd_en.port = PORTE,
    .lcd_en.pin = GPIO_PIN1,
    .lcd_en.direction = OUTPUT,
    .lcd_en.mode = DIO,
    .lcd_en.pinAttach = NO_ATTACH,
    .lcd_en.pinOutCurrent = PIN_CURRENT_2mA,
    .lcd_en.state = LOW,

    .lcd_rs.port = PORTE,
    .lcd_rs.pin = GPIO_PIN2,
    .lcd_rs.direction = OUTPUT,
    .lcd_rs.mode = DIO,
    .lcd_rs.pinAttach = NO_ATTACH,
    .lcd_rs.pinOutCurrent = PIN_CURRENT_2mA,
    .lcd_rs.state = LOW,

    .lcd_data_pins[0].port = PORTA,
    .lcd_data_pins[0].pin = GPIO_PIN2,
    .lcd_data_pins[0].direction = OUTPUT,
    .lcd_data_pins[0].mode = DIO,
    .lcd_data_pins[0].pinAttach = NO_ATTACH,
    .lcd_data_pins[0].pinOutCurrent = PIN_CURRENT_2mA,
    .lcd_data_pins[0].state = LOW,

    .lcd_data_pins[1].port = PORTA,
    .lcd_data_pins[1].pin = GPIO_PIN3,
    .lcd_data_pins[1].direction = OUTPUT,
    .lcd_data_pins[1].mode = DIO,
    .lcd_data_pins[1].pinAttach = NO_ATTACH,
    .lcd_data_pins[1].pinOutCurrent = PIN_CURRENT_2mA,
    .lcd_data_pins[1].state = LOW,

    .lcd_data_pins[2].port = PORTA,
    .lcd_data_pins[2].pin = GPIO_PIN4,
    .lcd_data_pins[2].direction = OUTPUT,
    .lcd_data_pins[2].mode = DIO,
    .lcd_data_pins[2].pinAttach = NO_ATTACH,
    .lcd_data_pins[2].pinOutCurrent = PIN_CURRENT_2mA,
    .lcd_data_pins[2].state = LOW,

    .lcd_data_pins[3].port = PORTA,
    .lcd_data_pins[3].pin = GPIO_PIN5,
    .lcd_data_pins[3].direction = OUTPUT,
    .lcd_data_pins[3].mode = DIO,
    .lcd_data_pins[3].pinAttach = NO_ATTACH,
    .lcd_data_pins[3].pinOutCurrent = PIN_CURRENT_2mA,
    .lcd_data_pins[3].state = LOW

};

button_t startButton = {
    .btn_pin.port = PORTF,
    .btn_pin.pin = GPIO_PIN4,
    .btn_pin.direction = INPUT,
    .btn_pin.mode = DIO,
    .btn_pin.pinAttach = PIN_PULLUP,
    .btn_pin.pinOutCurrent = PIN_CURRENT_2mA,
    .btn_pin.state = HIGH,

    .btn_state = RELEASED,

    .btn_conn = PULL_UP};

button_t stopButton = {
    .btn_pin.port = PORTF,
    .btn_pin.pin = GPIO_PIN0,
    .btn_pin.direction = INPUT,
    .btn_pin.mode = DIO,
    .btn_pin.pinAttach = PIN_PULLUP,
    .btn_pin.pinOutCurrent = PIN_CURRENT_2mA,
    .btn_pin.state = HIGH,

    .btn_state = RELEASED,

    .btn_conn = PULL_UP};

systick_t sys1 = {
    .systickClk = systickSystemClk,
    .systickInt = systickIntEnable,
    .systickHandler = Counter};
void stopWatchInit(void);

void displayTime(void);

void manageStopWatch(void);

#endif //_STOP_WATCH_