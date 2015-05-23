
#include <avr/io.h>
#include <util/delay.h>

#include "display.h"
void showDigit(char c);
static unsigned char value=0x56;
static unsigned char value2=0x79;
static unsigned char status=0;
enum  eMode { 
  TIME_MODE,
  HOUR_SET,
  MIN_SET,
  KITCHEN_SET,
  KITCHEN_RUN,
  KITCHEN_PAUSE  };
unsigned char curMode=TIME_MODE;
unsigned char timeCurSecond=0;
unsigned char timeCurMinute=0x00;
unsigned char timeCurHour=0x12;

unsigned char kitchenStart=0x01;
unsigned char kitchenStartTimeout;
unsigned char kitchenMinute;
unsigned char kitchenSecond;
unsigned char seconds=60;
unsigned char setTimeout=0;
unsigned char leftLong=0;
unsigned char getDisplay()
{
  return value;
}
void setDisplay(unsigned char v)
{
 value=v;

}
    char dot1=0;
    char dot2=1;
char dot1o;
char dot2o;
char bounce=0;

unsigned char dotDisplay=0;
unsigned char minor=0;
unsigned char inc(unsigned char v)
{
    char e=v&0xF;
    char z=(v >>4) &0xF ;
    if(v==0x99)
       return 0x99;
    if(e==9)
    {
       e=0;
       z++;
    }else{
       e++;
    }
    return e | (z<<4);
}
unsigned char dec(unsigned char v)
{
   char e=v&0xF;
   char z=(v>>4) &0xF;
   if(v==0)
    return 0;
   if(e==0)
   {
      z--;
      e=9;
   }else{
      e--;
   }
   return e | (z<<4);
}
void  everySecond()
{
  if(curMode==KITCHEN_SET)
  {
     kitchenStartTimeout--;
     if(kitchenStartTimeout==0)
     {
      curMode=TIME_MODE;
     }
   }
  
  if(dotDisplay & _BV(1) )
  {
     dotDisplay &=~ _BV(1) ;
  } else{ 
     dotDisplay |= _BV(1) ;
  }

  if(   curMode!=KITCHEN_PAUSE)
  {  
  if(kitchenMinute==0 && kitchenSecond==0)
  {
  }
  else
  {

	  if(kitchenSecond==0x00)
	  { 
           	    kitchenSecond=0x59;
		    kitchenMinute=dec(kitchenMinute);
         
	  }else{
	    kitchenSecond=dec(kitchenSecond);
	  }
  }
  }


  timeCurSecond=inc(timeCurSecond);
  if(timeCurSecond==0x60)
  {
     timeCurSecond=0;
     timeCurMinute=inc(timeCurMinute);
  }
  if(timeCurMinute==0x60)
  {
     timeCurMinute=0;
     timeCurHour=inc(timeCurHour);
  }
  if(timeCurHour==0x24)
     timeCurHour=0x00;

  if(dot2==1 )
  {
      leftLong++;
  }else{
    leftLong=0;
  }
  if(leftLong>5)
  {
     setTimeout=20;
     curMode=HOUR_SET;
  }
  if(curMode == HOUR_SET || curMode == MIN_SET)
  {
     if(setTimeout>0)
         setTimeout--;
     else
        curMode=TIME_MODE;
  }
}

void buttonLeft()
{
  if(curMode == HOUR_SET)
  {
     setTimeout=10;
     curMode = MIN_SET;
     timeCurSecond=0;
     return;
  }
  if(curMode == MIN_SET)
  {
     setTimeout=10;
     curMode = HOUR_SET;
     timeCurSecond=0;
     return;
  }


  if(curMode==TIME_MODE)
  {

     curMode=KITCHEN_SET;
     kitchenStart=0x01;
     return;
  }
  
  if(curMode==KITCHEN_RUN){
     kitchenMinute= kitchenStart;
     kitchenSecond= 0;

   return;
  }
  if(curMode==KITCHEN_PAUSE){
   curMode=KITCHEN_SET;
   return;
  }


  if(curMode==KITCHEN_SET)
  {
     kitchenStartTimeout=30;
     switch(kitchenStart)
     { 
        case 0x01:
        kitchenStart=0x06;
        return;
        case 0x06:
        kitchenStart=0x10;
        return;
        case 0x10:
        kitchenStart=0x18;
        return;
        case 0x18:
        kitchenStart=0x20;
        return;
        case 0x20:
        kitchenStart=0x25;
        return;
        case 0x25:
        kitchenStart=0x30;
        return;
        case 0x30:
        kitchenStart=0x60;
        return;

        case 0x60:
        kitchenStart=0x90;
        return;
        case 0x90:
        kitchenStart=0xFF;
        curMode=TIME_MODE;
        default:
        kitchenStart=0x01;
        return;

     }
  }
}
void buttonRight()
{

  if(curMode == HOUR_SET)
  {

     timeCurHour=inc(     timeCurHour);
     if(timeCurHour==0x24)
       timeCurHour=0x00;
     timeCurSecond=0;
     return;
  }
  if(curMode == MIN_SET)
  {
     timeCurMinute=inc(timeCurMinute);
     if(timeCurMinute==0x60)
       timeCurMinute=0x00;
     timeCurSecond=0;
     return;
  }


 if(curMode==KITCHEN_RUN){
   curMode=KITCHEN_PAUSE;
   return;
  }
 if(curMode==KITCHEN_PAUSE){
   curMode=KITCHEN_RUN;
   return;
  }

  if(curMode==KITCHEN_SET  )
  {
     curMode=KITCHEN_RUN;
     kitchenMinute= kitchenStart;
     kitchenSecond= 0;
  }
}
void displayPoll(){

  if( TIFR0  !=0)
    {
       TIFR0=7;
       minor--;


      if(bounce>0)
      {
        bounce--;
      } 
      else
      {
        if(dot1!=dot1o)
        {
            dot1o=dot1;
            if(dot1==0)
            {
               buttonRight();
               bounce=20;
            }
        }

        if(dot2!=dot2o)
        {
          dot2o=dot2;
          if(dot2==0)
          {
            buttonLeft();
            bounce=20;
          }
         }
      }



    }
  if(minor==0)
  {
     minor=200;
     everySecond();
  }


  if(PINB & _BV(2))
         {
            dot2=0;
         }else{
            dot2=1;
         }

         if(PINB & _BV(0)) 
         {
            dot1=0;
         }else{
            dot1=1;
         }

  if(status==0)
  {
    DDRD |= _BV(0) | _BV(1) | _BV(4) | _BV(5) | _BV(6) | _BV(7) ;
    DDRC = 0xFF;
    DDRB &= ~(_BV(2) | _BV(0)) ;
    PORTB |= (_BV(2) | _BV(0)) ;
   status=1;

    TCCR0A = 2; // use CTC no output
    TCCR0B = 5; // 1024scaler source
    OCR0A = 118;
    TIFR0=0;

   return;
  }
  if(curMode==KITCHEN_SET)
  {
    value=kitchenStart;
    value2=0xFF;
  }
  if(curMode==TIME_MODE)
  {
     value=timeCurHour;
     value2=timeCurMinute;
  }
  if(curMode==KITCHEN_RUN)
  {
     value=kitchenMinute;
     value2=kitchenSecond;
  }

 if(curMode == HOUR_SET)
  {
     value2=0xFF;
     value=timeCurHour;
  }
  if(curMode == MIN_SET)
  {
     value2=timeCurMinute;
     value=0xFF;
  }

  if(status==255)
    status=1;
    
  if(status>192 )
  {
      PORTD|= ( _BV(0) | _BV(1) | _BV(4) | _BV(5));
    showDigit((value >> 4) & 0x0F);
      PORTD|= ( _BV(0) | _BV(1) | _BV(4) | _BV(5));
      PORTD&= ~_BV(0);
      if(dotDisplay & _BV(0))
      {
         PORTD|=_BV(7);
      }
    status++;
   return;
  }
  if(status>128)
  {
      PORTD|= ( _BV(0) | _BV(1) | _BV(4) | _BV(5));
    showDigit(value & 0x0F);
      PORTD|= ( _BV(0) | _BV(1) | _BV(4) | _BV(5));
      PORTD&= ~_BV(1);
      if(dotDisplay & _BV(1))
      {
         PORTD|=_BV(7);
      }
    status++;
    return;
  }
  if(status>64)
  {
      PORTD|= ( _BV(0) | _BV(1) | _BV(4) | _BV(5));
    showDigit((value2 >> 4) & 0x0F);
      PORTD|= ( _BV(0) | _BV(1) | _BV(4) | _BV(5));
      PORTD&= ~_BV(4);
      if(dotDisplay & _BV(2))
      {
         PORTD|=_BV(7);
      }
    status++;
    return;
  }
  if(status>0)
  {
      PORTD|= ( _BV(0) | _BV(1) | _BV(4) | _BV(5));
    showDigit(value2 & 0x0F);
      PORTD|= ( _BV(0) | _BV(1) | _BV(4) | _BV(5));
      PORTD&= ~_BV(5);
      if(dotDisplay & _BV(3))
      {
         PORTD|=_BV(7);
      }
    status++;
    return;
  }

}


void showDigit(char c)
{
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
