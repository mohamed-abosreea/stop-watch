/*
 * systick.h
 *
 *  Created on: Aug 24, 2023
 *      Author: Mohamed Abosreea
 */

#ifndef MCAL_SYSTICK_SYSTICK_H_
#define MCAL_SYSTICK_SYSTICK_H_

/* Section : Includes */
#include "../../TM4C123GH6PM.h"
#include "../../std_lib.h"
#include "../../std_types.h"

/*  Section : Macro declarations */

#define F_CPU   16000000U
/*  Section : Macro Functions declarations */
#define SYSTICK_ENABLE()             (SysTick->CTRL |= (1U<<0))
#define SYSTICK_DISABLE()            (SysTick->CTRL &= ~(1U<<0))
#define SYSTICK_INTERRUPT_ENABLE()   (SysTick->CTRL |= (1U<<1))
#define SYSTICK_INTERRUPT_DISABLE()  (SysTick->CTRL &= ~(1U<<1))
#define SYSTICK_INTERNAL_CLK_SRC()   (SysTick->CTRL &= ~(1U<<2))
#define SYSTICK_SYSTEM_CLK_SRC()     (SysTick->CTRL |= (1U<<2))

/*  Section : Data types declarations */
typedef enum{
    systickIntDisable = 0,
    systickIntEnable
}systickInterrupt_t;


typedef enum{
    systicInternalCLk_4  = 0,
    systickSystemClk
}systickClkSrc_t;

typedef struct{
    systickInterrupt_t systickInt;
    systickClkSrc_t systickClk;
    void (*systickHandler)(void);
}systick_t;

/*  Section : Functions declarations */

Err_check_t systickInit(systick_t *systickConfig);

Err_check_t systickDeInit(systick_t *systickConfig);

Err_check_t systickSetBusyWait(uint32 secMs);

Err_check_t systickSetSingleInterval(systick_t *systickConfig , uint32 secMs);

Err_check_t systickSetPeriodicInterval(systick_t *systickConfig , uint32 secMs);


#endif /* MCAL_SYSTICK_SYSTICK_H_ */
