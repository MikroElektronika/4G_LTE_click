/*

Use mikroE Timer Calculator to generate proper timer configuration
and timer ISR.

https://www.mikroe.com/timer-calculator

*/
#include "Click_4G_LTE_types.h"

#define __4G_LTE_TIMER__

static void c4glte_configTimer()
{
    SREG_I_bit = 1; 
    TCCR1A = 0x80;
    TCCR1B = 0x09;
    OCR1AH = 0x1F; 
    OCR1AL = 0x3F; 
    OCIE1A_bit = 1; 
}

void Timer_interrupt() org IVT_ADDR_TIMER1_COMPA
{
    c4glte_tick();
}