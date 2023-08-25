#include "stop_watch.h"
void stopWatchInit(void)
{
    gpioPortClkEnable(PORTF);
    gpioPortClkEnable(PORTB);
    gpioPortClkEnable(PORTE);
    gpioPortClkEnable(PORTA);
    gpioPortClkEnable(PORTC);

    gpioPinInit(&RW);
    button_init(&startButton);
    button_init(&stopButton);
    lcd_init(&lcd1);
    lcd_send_command(&lcd1, _LCD_CLEAR);
    __delay_ms(10);
    lcd_send_string_pos(&lcd1, (uint8*)("Mohamed Ramadan") , ROW0 , COL0);
    lcd_send_string_pos(&lcd1, (uint8*)("Mohamed Abosreea") , ROW1 , COL0);
    __delay_ms(2000);
    lcd_send_command(&lcd1, _LCD_CLEAR);
    __delay_ms(10);
    lcd_send_string_pos(&lcd1, (uint8*)("Stop Watch") , ROW0 , COL3);
    __delay_ms(2000);
    lcd_send_command(&lcd1, _LCD_CLEAR);
    __delay_ms(10);
    led_init(&led1);
    led_turn_on(&led1);
    lcd_send_string_pos(&lcd1, (uint8*)"00:00:00", ROW0, COL0);
    button_get_state(&startButton, &startButtonState);
    while(startButtonState != PRESSED)
    {
        button_get_state(&startButton, &startButtonState);
    }
    startFlag++ ;
    startButtonState = RELEASED;
    
    systickInit(&sys1);
    systickSetPeriodicInterval(&sys1, 1000);
    stopButtonState = RELEASED;
}

void manageStopWatch(void)
{
    button_get_state(&startButton, &startButtonState);
        button_get_state(&stopButton, &stopButtonState);
        if(stopButtonState == PRESSED)
        {
            stopButtonState = RELEASED;
            stopFlag++ ;
            /*Pause Stop Watch*/
            if(stopFlag == 1)
            {
                SYSTICK_INTERRUPT_DISABLE();
                __delay_ms(250);
            }
            /*Reset Stop Watch*/
            if(stopFlag == 2)
            {
                count = 0 ;
                stopFlag = 0 ;
                startFlag = 0 ;
            }
            else{
                /*Do Nothing*/
            }
        }else
        {
            /*Do Nothing*/
        }

        if(startButtonState == PRESSED)
        {
            startButtonState = RELEASED;
            startFlag++ ;
            /*resume Stop Watch*/
            if(startFlag == 1)
            {
                systickSetPeriodicInterval(&sys1, 1000);
            }
        }else
        {
            /*Do Nothing*/
        }
}

void displayTime(void)
{
    hours = count / 3600 ;
        mins = (count - 3600*hours) / 60;
        secs = count % 60 ;
        if(hours >= 10)
        {
            lcd_send_number_pos(&lcd1, hours, ROW0, COL0);
        }else if(hours == 0)
        {
            lcd_send_string_pos(&lcd1, "00", ROW0, COL0);
        }
        else{
            lcd_send_number_pos(&lcd1, hours, ROW0, COL1);
        }

        lcd_send_chr_pos(&lcd1, ':', ROW0, COL2);
        if(mins >= 10)
        {
            lcd_send_number_pos(&lcd1, mins, ROW0, COL3);
        }else if(mins == 0)
        {
            lcd_send_string_pos(&lcd1, "00", ROW0, COL3);
        }
        else{
            lcd_send_number_pos(&lcd1, mins, ROW0, COL4);
        }
        lcd_send_chr_pos(&lcd1, ':', ROW0, COL5);
        if(secs >= 10)
        {
            lcd_send_number_pos(&lcd1, secs, ROW0, COL6);
        }else if (secs == 0)
        {
            lcd_send_string_pos(&lcd1, "00", ROW0, COL6);
        }
        else {
            lcd_send_number_pos(&lcd1, secs, ROW0, COL7);
        }
}

void Counter(void)
{
    count++;
    if (count >= 86400)
    {
        count = 0;
    }
    else
    {
        /*Do Nothing*/
    }
    led_toggle(&led1);
}