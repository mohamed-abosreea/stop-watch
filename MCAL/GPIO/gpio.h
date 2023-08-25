/*
 * gpio.h
 *
 *  Created on: Aug 17, 2023
 *      Author: Mohamed Abosreea
 */

#ifndef MCAL_GPIO_GPIO_H_
#define MCAL_GPIO_GPIO_H_

/*  Section : Includes*/
#include "../../std_lib.h"
#include "../../std_types.h"
#include "../../TM4C123GH6PM.h"

/*  Section : Macro declarations */
#define MAX_PORT_NUMBER 6
/*  Section : Macro Functions declarations */

/*  Section : Data types declarations */
typedef enum
{
    HIGH = 1 ,
    LOW = 0
}pinState_t;

typedef enum
{
    GPIO_PIN0 = 0 ,
    GPIO_PIN1 ,
    GPIO_PIN2 ,
    GPIO_PIN3 ,
    GPIO_PIN4 ,
    GPIO_PIN5 ,
    GPIO_PIN6 ,
    GPIO_PIN7
}pinNum_t;

typedef enum
{
    PORTA = 0,
    PORTB,
    PORTC,
    PORTD,
    PORTE,
    PORTF
}port_t;

typedef enum{
    INPUT = 0,
    OUTPUT
}pinDirection_t;

typedef enum{
    DIO = 0,
    PIN_DIO_INTERRUPT,
    ANALOG,
    ALTERNATE_FUNCTION
}pinMode_t;

typedef enum{
    PIN_OPENDRAIN = 0 ,
    PIN_PULLUP,
    PIN_PULLDOWN,
    NO_ATTACH
}pinInternalAttach_t;

typedef enum{
    PIN_CURRENT_2mA = 0 ,
    PIN_CURRENT_4mA,
    PIN_CURRENT_8mA,
    NO_CURRENT
}pinOutputCurrent;


typedef struct
{
    port_t port;
    pinNum_t pin ;
    pinDirection_t direction ;
    pinState_t state ;
    pinMode_t mode;
    pinInternalAttach_t pinAttach;
    pinOutputCurrent pinOutCurrent;

}pinConfig_t;

/*  Section : Functions declarations */

/**
 * This function is used to initialize a gpio pin.
 * @param pin [port - pinNum - mode - status - outputCurrent - attachment]
 * @return OK if function success fine , N_OK if function fails
 */
Err_check_t gpioPinInit(pinConfig_t* pin);
/**
 * This function is used to write a logic on a pin
 * @param pin [port - pinNum - mode - status - outputCurrent - attachment]
 * @param state [HIGH - LOW]
 * @return OK if function success fine , N_OK if function fails
 */
Err_check_t gpioGetPinSate(pinConfig_t* pin , pinState_t *state);
/**
 * This function is used to toggle a logic on a pin
 * @param pin [port - pinNum - mode - status - outputCurrent - attachment]
 * @param state [HIGH - LOW]
 * @return OK if function success fine , N_OK if function fails
 */
Err_check_t gpioTogglePinstate( pinConfig_t *pin_config);
/**
 * This function is used to write a logic on a pin
 * @param pin [port - pinNum - mode - status - outputCurrent - attachment]
 * @param state [HIGH - LOW]
 * @return OK if function success fine , N_OK if function fails
 */
Err_check_t gpioSetPinState(pinConfig_t* pin , pinState_t state);
/**
 * This function is used to write a logic on a pin
 * @param port [PORTA - PORTB - PORTC - PORTD - PORTE - PORTF]
 * @return OK if function success fine , N_OK if function fails
 */
Err_check_t gpioPortClkEnable(port_t port);
#endif /* MCAL_GPIO_GPIO_H_ */
