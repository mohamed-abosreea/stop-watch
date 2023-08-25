/* 
 * File:   led.h
 * Author: Mohamed Abosreea
 *
 * Created on March 25, 2023, 2:00 PM
 */

#ifndef LED_H
#define	LED_H
/* Section : Includes */
#include "led_cfg.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../std_lib.h"
#include "../../std_types.h"
/*  Section : Macro declarations */

/*  Section : Macro Functions declarations */

/*  Section : Data types declarations */
typedef enum {
    LED_OFF = 0,
    LED_ON
} led_state_t;

typedef struct
{
    port_t      port ;
    pinNum_t   pin ;
    led_state_t state ;
}led_t;
/*  Section : Functions declarations */
/**
 * This function is used to initialize a led
 * @param led [port_t - pin_num_t  - led_state_t]
 * @return OK if function success , N_OK if function fails
 */
Err_check_t led_init(const led_t *led);
/**
 * This function is used to get state of a led
 * @param led [port_t - pin_num_t  - led_state_t]
 * @param state [LED_ON - LED_OFF]
 * @return OK if function success , N_OK if function fails
 */
Err_check_t led_get_state(const led_t *led , led_state_t *state);
/**
 * This function is used to turn on a led
 * @param led [port_t - pin_num_t  - led_state_t]
 * @return OK if function success , N_OK if function fails
 */
Err_check_t led_turn_on(const led_t *led);
/**
 * This function is used to turn off a led
 * @param led [port_t - pin_num_t  - led_state_t]
 * @return OK if function success , N_OK if function fails
 */
Err_check_t led_turn_off(const led_t *led);
/**
 * This function is used to toggle a led
 * @param led [port_t - pin_num_t  - led_state_t]
 * @return OK if function success , N_OK if function fails
 */
Err_check_t led_toggle(const led_t *led);
#endif	/* LED_H */

