
#include "hw.h"
#include <avr/io.h>
#include <util/delay.h>

void showPosition(char p, char dotDisplay)
{
    switch(p)
    {
        case 0:
            PORTD&= ~_BV(0);
                  if(dotDisplay & _BV(0))
      {
         PORTD|=_BV(7);
      }
            break;
        case 1:
             PORTD&= ~_BV(1);
                   if(dotDisplay & _BV(1))
      {
         PORTD|=_BV(7);
      }
             break;
        case 2:
              PORTD&= ~_BV(4);
               if(dotDisplay & _BV(2))
      {
         PORTD|=_BV(7);
      }
              break;
        default:      
              PORTD&= ~_BV(5);
                if(dotDisplay & _BV(3))
      {
         PORTD|=_BV(7);
      }
              break;
                    
    }
    
}
void showDigit(char c)
{
      PORTD|= ( _BV(0) | _BV(1) | _BV(4) | _BV(5));
      // D7 off
      PORTD&=~_BV(7);
      PORTD&=~_BV(6);
      //PORTD|=_BV(7);
  switch(c)
  {
    case 0:
      PORTC=_BV(0) | _BV(1) | _BV(4) | _BV(3) | _BV(2) ;
      PORTD|=_BV(6);
      break;
    case 1:
      PORTC=_BV(2)  ;
      PORTD|=_BV(6);
      break;
    case 2:
      PORTC=_BV(2) | _BV(3) | _BV(5) | _BV(1) | _BV(0) ;
      break;
    case 3:
      PORTC=_BV(3) | _BV(2) | _BV(5) | _BV(0)  ;
      PORTD|=_BV(6);
      break;
    case 4:
      PORTC=_BV(4) | _BV(5) | _BV(2)   ;
      PORTD|=_BV(6);
      break;
    case 5:
      PORTC=_BV(3) | _BV(4) | _BV(5) | _BV(0)  ;
      PORTD|=_BV(6);
      break;
    case 6:
      PORTC=_BV(3) | _BV(4) | _BV(5) | _BV(0)  | _BV(1) ;
      PORTD|=_BV(6);

      break;
    case 7:
      PORTC=_BV(3) | _BV(2)  ;
      PORTD|=_BV(6);
      break;
    case 8:
      PORTC=_BV(0) | _BV(1) | _BV(2) | _BV(3)  | _BV(4) | _BV(5)  ;
      PORTD|=_BV(6);
      break;
    case 9:
      PORTC=_BV(0) |  _BV(2) | _BV(3)  | _BV(4) | _BV(5)  ;
      PORTD|=_BV(6);
      break;
    default:
      PORTC=0;
  }
}
extern boolean timerOverflow()
{
   if( TIFR0  !=0)
    {
       TIFR0=7;
       return TRUE;
    }
    return FALSE;
}
extern  char getButtonPressed()
{
    char ret;
      if(PINB & _BV(2))
         ret=_BV(0);
        if(PINB & _BV(0)) 
         ret|=_BV(1);   
}
void initHw()
{
        DDRD |= _BV(0) | _BV(1) | _BV(4) | _BV(5) | _BV(6) | _BV(7) ;
    DDRC = 0xFF;
    DDRB &= ~(_BV(2) | _BV(0)) ;
    PORTB |= (_BV(2) | _BV(0)) ;

    TCCR0A = 2; // use CTC no output
    TCCR0B = 5; // 1024scaler source
    OCR0A = 118;
    TIFR0=0;
}
