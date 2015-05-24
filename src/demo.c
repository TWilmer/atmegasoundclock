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
#include "sin.h"

/* ------------------------------------------------------------------------- */

int __attribute__((noreturn)) main(void)
{

   ADCSRA =0; // disable ADC to save power
   wdt_enable(WDTO_1S);
   PRR&=~_BV(PRTIM2); 
    /* Even if you don't use the watchdog, turn it off here. On newer devices,
     * the status of the watchdog (on/off, period) is PRESERVED OVER RESET!
     */

    TCCR2A =  0x00;
    TCCR2A |= _BV (COM2A1) | _BV (COM2B1) | _BV (WGM20);
    TCCR2A &= ~(_BV (COM2A0) | _BV (COM2B0));
    TCNT2 = 0; 
        PORTD &= ~(_BV (PORTD3));
	 DDRD |= _BV (DDD3);
        uint8_t l=0;
	  TCCR2B |= _BV (CS20);
    uint8_t count=0;
    uint8_t level=0;
    uint8_t delay=0;
    uint8_t n=0;
    uint8_t i=0;
 
    for(;;){                /* main event loop */
	i++;
                OCR2B=pgm_read_byte_near(sine+i);
        wdt_reset();
        displayPoll();
    }
}

/* ------------------------------------------------------------------------- */
