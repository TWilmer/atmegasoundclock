;
; "BCD2bin8" - BCD to 8-bit binary conversion
;
; This subroutine converts a 2-digit BCD number (temp2:temp1) to an
; 8-bit number (temp1).
;
; Subroutine Register Variables
; 	temp1	binary result
; 	temp1	lower digit of BCD input
; 	temp2	higher digit of BCD input

        .text
.global Bin2bcd8
        .type   Bin2bcd8, @function

      


Bin2bcd8:
	clr		r25		; clear result MSD
bBCD8_1:
	subi	r24,10	; input = input - 10
	brcs	bBCD8_2		; abort if carry set
	inc		r25  		; inc MSD
	rjmp	bBCD8_1		; loop again
bBCD8_2:
	subi	r24,-10	; compensate extra subtraction
	ret
	
 .size   Bin2bcd8, .-Bin2bcd8
   
