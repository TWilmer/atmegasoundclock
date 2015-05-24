

char v0;
char v1;
char v2;
char v3;
char dotDisplay;


 void setDotDisplay(char dots)
 {
    dotDisplay=dots;
 }
 void setDisplay(char inv0, char inv1, char inv2, char inv3)
{
  v0=inv0;
  v1=inv1;
  v2=inv2;
  v3=inv3;
}
unsigned char state=0;

void doMultiPlex()
{
    state++;
   if(state>0 && state < 64)
   {
     showDigit(v0);
     showPosition(0, dotDisplay);
   }
   if(state>64 && state < 128)
   {
     showDigit(v1);
     showPosition(1, dotDisplay);
   }
   if(state>128 && state < 192)
   {
     showDigit(v2);
     showPosition(2, dotDisplay);
   }
   if(state>192 && state < 255)
   {
      showDigit(v3);
      showPosition(3, dotDisplay);
   }
}
