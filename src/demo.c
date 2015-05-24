/* Name: main.c
 * Project: custom-class, a basic USB example
 * Author: Christian Starkjohann
 * Creation Date: 2008-04-09
 * Tabsize: 4
 * Copyright: (c) 2008 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 */

/*
This example should run on most AVRs with only little changes. No special
hardware resources except INT0 are used. You may have to change usbconfig.h for
different I/O pins for USB. Please note that USB D+ must be the INT0 pin, or
at least be connected to INT0 as well.
We assume that an LED is connected to port B bit 0. If you connect it to a
different port or bit, change the macros below:
*/
#define LED_PORT_DDR        DDRB
#define LED_PORT_OUTPUT     PORTB
#define LED_BIT             0

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>  /* for sei() */
#include <util/delay.h>     /* for _delay_ms() */

#include "hw.h"
#include "BCD2bin8.h"
#include "time.h"
#include "sound.h"
/* ------------------------------------------------------------------------- */



int __attribute__((noreturn)) main(void)
{
   wdt_enable(WDTO_1S);


   CLKPR=_BV(CLKPCE) | 0;
   CLKPR=0;
   ADCSRA =0; // disable ADC to save power
   PRR&=~_BV(PRTIM2);
   PRR&=~_BV(PRTIM1);
   PRR&=~_BV(PRTIM0);   
    /* Even if you don't use the watchdog, turn it off here. On newer devices,
     * the status of the watchdog (on/off, period) is PRESERVED OVER RESET!
     */


    soundInit();
 initTime();

 initHw();
    ;
    for(;;){                /* main event loop */
        
        wdt_reset();
        doTimeTick();
        setDotDisplay(5);
        uint16_t v=Bin2bcd8(getMinutes());
           uint16_t v2=Bin2bcd8(getSeconds());  
       setDisplay( v >> 8, v ,v2>>8,v2);
       if(40==getSeconds())
       {
          playClock();
       }
       if(10==getSeconds())
       {
          playGo();
       }
       if(20==getSeconds())
       {
          playFinished();
       }
       if(25==getSeconds())
       {
          playTimer();
       }
       if(5==getSeconds())
       {
          playHour();
       }
       if(35==getSeconds())
       {
          playMinute();
       }
      doMultiPlex();
         PIND=_BV(2);
        
      
    }
   
}

/* ------------------------------------------------------------------------- */
