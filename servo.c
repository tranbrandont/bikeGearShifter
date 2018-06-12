#include "lpc1114.h"
#include "servo.h"
__attribute__((constructor)) void servosetup() {
  SYSCON.SYSAHBCLKCTRL.CT16B1 = 1;
  SYSCON.SYSAHBCLKCTRL.IOCON  = 1;
  IOCON.PIO1_9.FUNC = 1;
  SYSCON.SYSAHBCLKCTRL.IOCON = 0;

  TMR16B1.PR          = 48;
  TMR16B1.MR3         = 20000;
  TMR16B1.MR0         = 18500;
  TMR16B1.MR1         = 20000;
  TMR16B1.MCR.MR1I    = 1;

  TMR16B1.MCR.MR3R    = 1;
  TMR16B1.PWMC.PWMEN0 = 1;

  TMR16B1.TC      = 0;
  TMR16B1.PC      = 0;

  TMR16B1.TCR.CEn = 1;
}
