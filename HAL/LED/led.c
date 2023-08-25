#include "led.h"

#if (ENABLE_LED_APIS == ENABLE_LED)
Err_check_t led_init(const led_t *led)
{
    Err_check_t e_check = OK ;
    if(NULL == led)
    {
        e_check = N_OK ;
    }
    else
    {
        pinConfig_t pin_config ;
        pin_config.port = led ->port ;
        pin_config.pin = led ->pin ;
        pin_config.direction = OUTPUT ;
        pin_config.mode = DIO;
        pin_config.pinAttach = NO_ATTACH;
        pin_config.pinOutCurrent = PIN_CURRENT_2mA;
        pin_config.state = (pinState_t)led ->state;
        e_check =  gpioPinInit(&pin_config);
    }
    return e_check ;
}
#endif

#if (ENABLE_LED_APIS == ENABLE_LED)
Err_check_t led_get_state(const led_t *led , led_state_t *state)
{
    Err_check_t e_check = OK ;
    if(NULL == led || NULL == state)
    {
        e_check = N_OK ;
    }
    else
    {
        pinConfig_t pin_config ;
        pin_config.port = led ->port ;
        pin_config.pin = led ->pin ;
        pin_config.direction = OUTPUT ;
        pin_config.mode = DIO;
        pin_config.pinAttach = NO_ATTACH;
        pin_config.pinOutCurrent = PIN_CURRENT_2mA;
        pin_config.state = (pinState_t)led -> state;
        e_check =  gpioGetPinSate(&pin_config , (pinState_t *)state);
    }
    return e_check ;
}
#endif

#if (ENABLE_LED_APIS == ENABLE_LED)
Err_check_t led_turn_on(const led_t *led)
{
    Err_check_t e_check = OK ;
    if(NULL == led)
    {
        e_check = N_OK ;
    }
    else
    {
        pinConfig_t pin_config ;
        pin_config.port = led ->port ;
        pin_config.pin = led ->pin ;
        pin_config.direction = OUTPUT ;
        pin_config.mode = DIO;
        pin_config.pinAttach = NO_ATTACH;
        pin_config.pinOutCurrent = PIN_CURRENT_2mA;
        pin_config.state = HIGH;
        e_check =  gpioSetPinState(&pin_config , pin_config.state);
    }
    return e_check ;
}
#endif

#if (ENABLE_LED_APIS == ENABLE_LED)
Err_check_t led_turn_off(const led_t *led)
{
    Err_check_t e_check = OK ;
    if(NULL == led)
    {
        e_check = N_OK ;
    }
    else
    {
        pinConfig_t pin_config ;
        pin_config.port = led ->port ;
        pin_config.pin = led ->pin ;
        pin_config.direction = OUTPUT ;
        pin_config.mode = DIO;
        pin_config.pinAttach = NO_ATTACH;
        pin_config.pinOutCurrent = PIN_CURRENT_2mA;
        pin_config.state = LOW;
        e_check =  gpioSetPinState(&pin_config , pin_config.state);
    }
    return e_check ;
}
#endif

#if (ENABLE_LED_APIS == ENABLE_LED)
Err_check_t led_toggle(const led_t *led)
        {
    Err_check_t e_check = OK ;
    if(NULL == led)
    {
        e_check = N_OK ;
    }
    else
    {
        pinConfig_t pin_config ;
        pin_config.port = led ->port ;
        pin_config.pin = led ->pin ;
        pin_config.direction = OUTPUT ;
        pin_config.mode = DIO;
        pin_config.pinAttach = NO_ATTACH;
        pin_config.pinOutCurrent = PIN_CURRENT_2mA;
        pin_config.state = (pinState_t)led ->state;
        e_check =  gpioTogglePinstate(&pin_config);
    }
    return e_check ;
}
#endif
