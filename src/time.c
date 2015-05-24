

#include "time.h"
#include <avr/io.h>
#include <avr/interrupt.h> 
volatile uint8_t msCounter10thms=0;
volatile uint8_t seconds=0;
volatile uint8_t minutes=0;
volatile uint8_t hours=12;
void initTime()
{
       OCR0A=120;
    TCCR0A=0;
    TCCR0B=_BV(CS10); 
   
    TIMSK0=_BV(OCIE0A);
}
ISR(TIMER0_COMPA_vect)
{
   
    TCNT0=0;
    msCounter10thms++;
}

void doTimeTick()
{
  if(msCounter10thms>100)
        {
            msCounter10thms=0;
            seconds++;
            if(seconds>59)
            {
               seconds=0;
               minutes++;
               if(minutes>59)
               {
                   minutes=0;
                   hours++;
                   if(hours>23)
                   {
                      hours=0;
                   }
                   
               }
            }
        }
}

char getMinutes()
{
   return minutes;
}
char getHours()
{
return hours;
}
char getSeconds()
{
  return seconds;
}
