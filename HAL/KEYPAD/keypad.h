/* 
 * File:   keypad.h
 * Author: Mohamed Abosreea
 *
 * Created on April 12, 2023, 11:14 PM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H

/* Section : Includes */
#include "keypad_cfg.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../std_lib.h"
#include "../../std_types.h"
/*  Section : Macro declarations */
#define KEYPAD_ROWS   4
#define KEYPAD_COLS   4

/*  Section : Macro Functions declarations */

/*  Section : Data types declarations */
typedef struct 
{
    pinConfig_t keypad_rows[KEYPAD_ROWS];
    pinConfig_t keypad_cols[KEYPAD_COLS];
}keypad_t;
/*  Section : Functions declarations */

/**
 * This function is used to initialize a keypad
 * @param keypad [keypad_rows , keypad_cols]
 * @return OK if function success , N_OK if function fails
 */
Err_check_t keypad_init(keypad_t *keypad );
/**
 * This function is used to get value of a keypad button
 * @param keypad [keypad_rows , keypad_cols]
 * @param value [return value of pressed key]
 * @return OK if function success , N_OK if function fails
 */
Err_check_t keypad_get_value(keypad_t *keypad , uint8 *value);
        
#endif	/* KEYPAD_H */

