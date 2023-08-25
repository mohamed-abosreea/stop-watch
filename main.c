#include "stop_watch.h"

void main(void)
{
    stopWatchInit();
    while (1)
    {
        manageStopWatch();
        displayTime();
    }
}

void __delay_ms(int n)
{
    volatile int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < 3500; j++)
        {
        } /* do nothing for 1 ms */
}

void __delay_us(int n)
{
    volatile int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < 5; j++)
        {
        } /* do nothing for 1 us */
}


