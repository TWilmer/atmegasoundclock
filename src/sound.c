#include <avr/io.h>
#include <avr/interrupt.h> 
#include "finished.u8.h"
#include "go.u8.h"
#include "clock.u8.h"
#include "hour.u8.h"
#include "minute.u8.h"
#include "timer.u8.h"
volatile uint16_t sample=0;
volatile uint16_t end=0;
volatile uint8_t file=0;
ISR(TIMER1_COMPA_vect)
{
     TCNT1H=0;
     TCNT1L=0;


     if(file!=0)
     {        
          OCR2B=pgm_read_byte_near(sample);
             sample++;
         if(sample==end)
         {
             file=0;
            OCR2B=0;
          
         }
          
      }   
    
     
} 
void playFinished()
{
  if(file==0)
 {
    sample=finished;
    end=finished_count+finished;
    file=1;
  }
}
 void playGo()
{
   if(file==0)
 {
    sample=go;
    end=go_count+go-1;
    file=1;
  }
}
 void playClock()
{
    if(file==0)
 {
    sample=clock;
    end=clock_count+clock-1;
    file=1;
  }
}
 void playTimer()
{
    if(file==0)
 {
    sample=timer;
    end=timer+timer_count-1;
    file=1;
  }
}
 void playHour()
{
    if(file==0)
 {
    sample=hour;
    end=hour_count+hour-1;
    file=1;
  }
}
void playMinute()
{
    if(file==0)
 {
    sample=minute;
    end=minute_count+minute-1;
    file=1;
  }
}

void soundInit()
{
    TCCR2A =  0x00;
    TCCR2A |= _BV (COM2B1) | _BV (WGM20) | _BV (WGM21);
  
    TCNT2 = 0; 
        PORTD &= ~(_BV (PORTD3));
	 DDRD |= _BV (DDD3) | _BV (DDD2);

        uint8_t l=0;
	  TCCR2B |= _BV (CS20);
    uint8_t count=0;
    uint8_t level=0;
    uint8_t delay=0;
    uint8_t n=0;
    uint8_t i=0;
    
    sei	();	

    
    TCCR1A=0;
    TCCR1B=_BV(CS10); // set prescalere
    TIMSK1=_BV(OCIE1A);
    OCR1AH=((1500 >> 8) &0xFF);
    OCR1AL=(1500 &0xFF);
}
