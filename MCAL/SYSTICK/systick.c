/*
 * systick.c
 *
 *  Created on: Aug 24, 2023
 *      Author: Mohamed Abosreea
 */

#include "systick.h"

static void (*funcPtr)(void) = NULL;
static uint8 systickModeFlag ;
Err_check_t systickInit(systick_t *systickConfig)
{
    Err_check_t e_check = OK;
    if(NULL == systickConfig)
    {
        e_check = N_OK;
    }else{
        SYSTICK_DISABLE();
        /*Clear Current Value register by writing a value*/
        SysTick->VAL = 0 ;
        /*Manage Interrupt [Enable or Disable]*/
        MODIFY_BIT(SysTick->CTRL , 1 ,systickConfig->systickInt);
        /*Manage Clock Source [Internal Clock div by 4 - System CLock]*/
        MODIFY_BIT(SysTick->CTRL , 2 ,systickConfig->systickClk);
    }
    return e_check;
}

Err_check_t systickDeInit(systick_t *systickConfig)
{
    Err_check_t e_check = OK;
    if(systickConfig == NULL)
    {
        e_check = N_OK;
    }else{
        SYSTICK_DISABLE();
        SYSTICK_INTERRUPT_DISABLE();
        SysTick->VAL = 0 ;
        SysTick->LOAD = 0;
    }
    return e_check;
}

Err_check_t systickSetBusyWait(uint32 secMs)
{
    Err_check_t e_check = OK;
    SYSTICK_DISABLE();
    SYSTICK_INTERRUPT_DISABLE();
    SYSTICK_SYSTEM_CLK_SRC();
    uint32 value = (f32)(secMs) * F_CPU/1000.0;
    /*Set Preload Value*/
    SysTick->LOAD = value - 1;
    /*Clear Current Value register by writing a value*/
    SysTick->VAL = 0 ;
    SYSTICK_ENABLE();
    while(GET_BIT(SysTick->CTRL , 16) == 0);
    SysTick->VAL = 0 ;
    return e_check;
}

Err_check_t systickSetSingleInterval(systick_t *systickConfig , uint32 secMs)
{
    Err_check_t e_check = OK;
    if(systickConfig == NULL)
    {
        e_check = N_OK;
    }else{
        systickModeFlag = 1 ;
        SYSTICK_DISABLE();
        SYSTICK_INTERRUPT_ENABLE();
        /*Manage Clock Source [Internal Clock div by 4 - System CLock]*/
        MODIFY_BIT(SysTick->CTRL , 2 ,systickConfig->systickClk);
        uint32 value = (f32)(secMs) * F_CPU/1000.0;
        /*Set Preload Value*/
        SysTick->LOAD = value - 1;
        /*Clear Current Value register by writing a value*/
        SysTick->VAL = 0 ;
        if(systickConfig ->systickHandler != NULL)
        {
            funcPtr = systickConfig ->systickHandler;
        }else{
            e_check = N_OK;
            SYSTICK_INTERRUPT_DISABLE();
        }
        SYSTICK_ENABLE();
    }
    return e_check;
}

Err_check_t systickSetPeriodicInterval(systick_t *systickConfig , uint32 secMs)
{
    Err_check_t e_check = OK;
    if(systickConfig == NULL)
    {
        e_check = N_OK;
    }else{

        SYSTICK_DISABLE();
        SYSTICK_INTERRUPT_ENABLE();
        /*Manage Clock Source [Internal Clock div by 4 - System CLock]*/
        MODIFY_BIT(SysTick->CTRL , 2 ,systickConfig->systickClk);
        uint32 value = (f32)(secMs) * F_CPU/1000.0;
        /*Set Preload Value*/
        SysTick->LOAD = value - 1;
        /*Clear Current Value register by writing a value*/
        SysTick->VAL = 0 ;
        if(systickConfig ->systickHandler != NULL)
        {
            funcPtr = systickConfig ->systickHandler;
        }else{
            e_check = N_OK;
            SYSTICK_INTERRUPT_DISABLE();
        }
        SYSTICK_ENABLE();
    }
    return e_check;
}

void Systick_Handler(void)
{
    if(funcPtr != NULL)
    {
        if(systickModeFlag == 1)
        {
            SYSTICK_DISABLE();
            SYSTICK_INTERRUPT_DISABLE();
            SysTick->VAL = 0 ;
            SysTick->LOAD = 0;
            systickModeFlag = 0 ;

        }else{
            /*Do Nothing*/
        }
        funcPtr();
    }
}








