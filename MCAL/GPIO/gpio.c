/*
 * gpio.c
 *
 *  Created on: Aug 17, 2023
 *      Author: Mohamed Abosreea
 */
#include "gpio.h"

static GPIOA_Type* GPIO_PORTS[] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF};

static Err_check_t setPinDirection(pinConfig_t* pin);
static Err_check_t setPinAttach(pinConfig_t* pin);
static Err_check_t setPinCurrent(pinConfig_t* pin);
static Err_check_t setPinMode(pinConfig_t* pin);
static Err_check_t setDefaultState(pinConfig_t* pin);
static Err_check_t unlockPin(pinConfig_t* pin);
Err_check_t gpioPinInit(pinConfig_t* pin)
{
    Err_check_t e_check = OK;
    if(pin == NULL)
    {
        e_check = N_OK;
    }else{
        e_check &= unlockPin(pin);
        e_check &= setPinDirection(pin);
        e_check &= setPinMode(pin);
        e_check &= setPinAttach(pin);
        e_check &= setPinCurrent(pin);
        e_check &= setDefaultState(pin);
    }
    return e_check;
}

Err_check_t gpioGetPinSate(pinConfig_t* pin , pinState_t *state)
{
    Err_check_t e_check = OK;
    if(pin == NULL || state == NULL)
    {
        e_check = N_OK;
    }else{

        *state = (pinState_t)GET_BIT(GPIO_PORTS[pin->port]->DATA,pin->pin);
    }
    return e_check;
}

Err_check_t gpioTogglePinstate( pinConfig_t *pin_config) {
    Err_check_t e_check = OK;
    if (NULL == pin_config) {
        e_check = N_OK;
    } else {
        TOGGLE_BIT(GPIO_PORTS[pin_config ->port]->DATA, pin_config ->pin);
        e_check = OK;
    }
    return e_check;
}

Err_check_t gpioSetPinState(pinConfig_t* pin , pinState_t state)
{
    Err_check_t e_check = OK;
    if(pin == NULL)
    {
        e_check = N_OK;
    }else{

        MODIFY_BIT(GPIO_PORTS[pin->port]->DATA,pin->pin,state);
    }
    return e_check;
}

Err_check_t gpioPortClkEnable(port_t port)
{
    Err_check_t e_check = OK ;
    SYSCTL->RCGCGPIO |= (1<<port);
    //SYSCTL_RCGCGPIO_R |= (1<<port);
    return e_check;
}
static Err_check_t setPinDirection(pinConfig_t* pin)
{
    Err_check_t e_check = OK;
    if(pin == NULL)
    {
        e_check = N_OK;
    }else{
        MODIFY_BIT(GPIO_PORTS[pin->port]->DIR, pin->pin , pin->direction);

    }
    return e_check;
}
static Err_check_t setPinAttach(pinConfig_t* pin)
{
    Err_check_t e_check = OK;
    if(pin == NULL)
    {
        e_check = N_OK;
    }else{

        switch(pin->pinAttach)
            {
            case PIN_OPENDRAIN:
                SET_BIT(GPIO_PORTS[pin->port]->ODR,pin->pin);
                break;
            case PIN_PULLDOWN:
                SET_BIT(GPIO_PORTS[pin->port]->PDR,pin->pin);
                CLEAR_BIT(GPIO_PORTS[pin->port]->PUR , pin->pin);
                break;
            case PIN_PULLUP:
                SET_BIT(GPIO_PORTS[pin->port]->PUR ,pin->pin);
                CLEAR_BIT(GPIO_PORTS[pin->port]->PDR , pin->pin);
                break;
            case NO_ATTACH:
                CLEAR_BIT(GPIO_PORTS[pin->port]->PUR ,pin->pin);
                CLEAR_BIT(GPIO_PORTS[pin->port]->PDR , pin->pin);
                break;
            default:
                CLEAR_BIT(GPIO_PORTS[pin->port]->PUR ,pin->pin);
                CLEAR_BIT(GPIO_PORTS[pin->port]->PDR , pin->pin);
                CLEAR_BIT(GPIO_PORTS[pin->port]->ODR,pin->pin);
            }
    }
    return e_check;
}

static Err_check_t setPinCurrent(pinConfig_t* pin)
{
    Err_check_t e_check = OK;
    if(pin == NULL)
    {
        e_check = N_OK;
    }else{

        switch(pin->pinOutCurrent)
            {
            case PIN_CURRENT_2mA:
                SET_BIT(GPIO_PORTS[pin->port]->DR2R,pin->pin);
                CLEAR_BIT(GPIO_PORTS[pin->port]->DR4R, pin->pin);
                CLEAR_BIT(GPIO_PORTS[pin->port]->DR8R, pin->pin);
                break;
            case PIN_CURRENT_4mA:
                SET_BIT(GPIO_PORTS[pin->port]->DR4R,pin->pin);
                CLEAR_BIT(GPIO_PORTS[pin->port]->DR8R , pin->pin);
                break;
            case PIN_CURRENT_8mA:
                SET_BIT(GPIO_PORTS[pin->port]->DR8R,pin->pin);
                break;
            case NO_CURRENT:
                CLEAR_BIT(GPIO_PORTS[pin->port]->DR2R, pin->pin);
                CLEAR_BIT(GPIO_PORTS[pin->port]->DR4R, pin->pin);
                CLEAR_BIT(GPIO_PORTS[pin->port]->DR8R, pin->pin);
                break;
            default:
                ;
            }
    }
    return e_check;
}

static Err_check_t setPinMode(pinConfig_t* pin)
{
    Err_check_t e_check = OK;
    if(pin == NULL)
    {
        e_check = N_OK;
    }else{

        switch(pin->mode)
            {
            case DIO:
                SET_BIT(GPIO_PORTS[pin->port]->DEN,pin->pin);
                CLEAR_BIT(GPIO_PORTS[pin->port]->AFSEL, pin->pin);
                CLEAR_BIT(GPIO_PORTS[pin->port]->IM , pin->pin);
                break;
            case ALTERNATE_FUNCTION:
                SET_BIT(GPIO_PORTS[pin->port]->AFSEL,pin->pin);
                CLEAR_BIT(GPIO_PORTS[pin->port]->DEN , pin->pin);
                CLEAR_BIT(GPIO_PORTS[pin->port]->IM , pin->pin);
                break;
            case PIN_DIO_INTERRUPT:
                SET_BIT(GPIO_PORTS[pin->port]->DEN,pin->pin);
                SET_BIT(GPIO_PORTS[pin->port]->IM , pin->pin);
                CLEAR_BIT(GPIO_PORTS[pin->port]->AFSEL, pin->pin);
                break;
            default:
                ;
            }
    }
    return e_check;
}
static Err_check_t setDefaultState(pinConfig_t* pin)
{
    Err_check_t e_check = OK;
    if(pin == NULL)
    {
        e_check = N_OK;
    }else{

        MODIFY_BIT(GPIO_PORTS[pin->port]->DATA,pin->pin,pin->state);
    }
    return e_check;
}

static Err_check_t unlockPin(pinConfig_t* pin)
{
    Err_check_t e_check = OK;
    if(pin == NULL)
    {
        e_check = N_OK;
    }else{
        switch(pin->port)
        {
        case PORTA:
            break;
        case PORTB:
            GPIO_PORTS[PORTB]->LOCK = 0x4C4F434B;
            GPIO_PORTS[PORTB]->CR = 0xFF;
            break;
        case PORTC:
            break;
        case PORTD:
            GPIO_PORTS[PORTD]->LOCK = 0x4C4F434B;
            GPIO_PORTS[PORTD]->CR = 0xFF;
            break;
        case PORTE:
            break;
        case PORTF:
            GPIO_PORTS[PORTF]->LOCK = 0x4C4F434B;
            GPIO_PORTS[PORTF]->CR = 0xFF;
            break;
        default:
            ;
        }
    }
    return e_check;
}
