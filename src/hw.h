#pragma once

enum {FALSE=0, TRUE=1};
typedef char boolean;
extern void initHw();
extern void showDigit(char c);
extern void showPosition(char p, char dotDisplay);
extern  char getButtonPressed();
