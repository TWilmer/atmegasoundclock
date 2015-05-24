
#include <avr/io.h>
uint8_t toBCD(uint8_t v)
{
    uint8_t temp2=0;
    uint8_t temp1=v;
    
    temp1=temp1-10;
    return temp1;
    
}
uint8_t getBDC10(uint8_t v);
uint8_t getBDC1(uint8_t v);
