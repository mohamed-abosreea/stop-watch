/* 
 * File:   lcd.h
 * Author: Mohamed Absoreea
 *
 * Created on May 1, 2023, 9:47 PM
 */

#ifndef LCD_H
#define	LCD_H
/* Section : Includes */
#include "lcd_cfg.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../std_lib.h"
#include "../../std_types.h"
#include <stdlib.h>

/*  Section : Macro declarations */
#define _LCD_CLEAR                  0x01
#define _LCD_RETURN_HOME            0x02
#define _LCD_ENTRY_MODE_DEC_SHIFT_OFF   0x04
#define _LCD_ENTRY_MODE_DEC_SHIFT_ON    0x05
#define _LCD_ENTRY_MODE_INC_SHIFT_OFF   0x06
#define _LCD_ENTRY_MODE_INC_SHIFT_ON    0x07
#define _LCD_ENTRY_MODE             0x06
#define _LCD_CURSOR_OFF_DISPLAY_ON  0x0C
#define _LCD_CURSOR_OFF_DISPLAY_OFF 0x08
#define _LCD_CUROSR_ON_BLINK_ON     0x0F
#define _LCD_CURSOR_ON_BLINK_ON     0x0E
#define _LCD_DISPLAY_SHIFT_LEFT     0x18
#define _LCD_DISPLAY_SHIFT_RIGHT    0x1C
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF 0x0C
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON  0x0D
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF  0x0E
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_ON   0x0F
#define _LCD_8BIT_2LINE             0x38
#define _LCD_4BIT_2LINE             0x28
#define _LCD_8BIT_1LINE             0x30
#define _LCD_4BIT_1LINE             0x20
#define _LCD_CGRAM_START            0x40
#define _LCD_DDRAM_START            0x80
/*  Section : Macro Functions declarations */

/*  Section : Data types declarations */
typedef enum {
    ROW0 = 0,
    ROW1,
    ROW2,
    ROW3
} row_t;

typedef enum {
    COL0 = 0,COL1,COL2,COL3,COL4,COL5,COL6,COL7,COL8,COL9,
    COL10,COL11,COL12,COL13,COL14,COL15,COL16,COL17,COL18,COL19
}col_t;

typedef enum {
    _4_BIT = 0,
    _8_BIT
} lcd_connection_t;

typedef struct {
    pinConfig_t lcd_en;
    pinConfig_t lcd_rs;
    pinConfig_t lcd_data_pins[8];
    lcd_connection_t lcd_connection;
}lcd_t;
/*  Section : Functions declarations */
/**
 * This function is used to initialize an lcd
 * @param lcd
 * @return OK if function success , N_OK if function fails
 */
Err_check_t lcd_init( lcd_t *lcd);
/**
 * This function is used to send command to an lcd
 * @param lcd
 * @param command
 * @return OK if function success , N_OK if function fails
 */
Err_check_t lcd_send_command( lcd_t *lcd, uint8 command);
/**
 * This function is used to send character to an lcd
 * @param lcd
 * @param character
 * @return OK if function success , N_OK if function fails
 */
Err_check_t lcd_send_chr( lcd_t *lcd, uint8 character);
/**
 * This function is used to send character at certain position
 * @param lcd
 * @param character
 * @param row
 * @param col
 * @return OK if function success , N_OK if function fails
 */
Err_check_t lcd_send_chr_pos( lcd_t *lcd, uint8 character, row_t row, col_t col);
/**
 * This function is used to display string
 * @param lcd
 * @param data
 * @return OK if function success , N_OK if function fails
 */
Err_check_t lcd_send_string( lcd_t *lcd, uint8* data);
/**
 * This function is used to display string at certain position
 * @param lcd
 * @param data
 * @param row
 * @param col
 * @return OK if function success , N_OK if function fails
 */
Err_check_t lcd_send_string_pos( lcd_t *lcd, uint8 * data, row_t row, col_t col);
/**
 * This function is used to display integer number at a certain position
 * @param lcd
 * @param num
 * @param row
 * @param col
 * @return OK if function success , N_OK if function fails
 */
Err_check_t lcd_send_number_pos( lcd_t *lcd, uint16 num, row_t row, col_t col);
/**
 * This function is used to display integer number
 * @param lcd
 * @param num
 * @return OK if function success , N_OK if function fails
 */
Err_check_t lcd_send_number( lcd_t *lcd, uint16 num);
/**
 * This function is used to display float number
 * @param lcd
 * @param num
 * @return OK if function success , N_OK if function fails
 */
Err_check_t lcd_send_floatNumber(lcd_t *lcd, f32 num);
/**
 * This function is used to display a custom character at a certain position
 * @param lcd
 * @param arr
 * @param mem_pos
 * @param row
 * @param col
 * @return OK if function success , N_OK if function fails
 */
Err_check_t lcd_send_custome_chr_pos( lcd_t *lcd, uint8 arr[], uint8 mem_pos, row_t row, col_t col);
/**
 * This function is used to set cursor at a specific location
 * @param lcd
 * @param row
 * @param col
 * @return OK if function success , N_OK if function fails
 */
Err_check_t lcd_set_cursor(lcd_t *lcd, row_t row, col_t col);

#endif	/* LCD_H */

