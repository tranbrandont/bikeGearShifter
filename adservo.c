#include "lpc1114.h"
volatile unsigned* _GPIO1ALL = (unsigned*) 0x50013ffc;
void setup() {
  SYSCON.SYSAHBCLKCTRL.CT16B1 = 1;
  SYSCON.SYSAHBCLKCTRL.IOCON  = 1;
  SYSCON.SYSAHBCLKCTRL.ADC = 1;
  SYSCON.PDRUNCFG.ADC_PD = 0;
  IOCON.PIO1_9.FUNC = 1;
  IOCON.R_PIO0_11.FUNC = 2;
  IOCON.R_PIO0_11.ADMODE = 0;
  SYSCON.SYSAHBCLKCTRL.IOCON = 0;
  AD0.CR.SEL = 1;
  AD0.CR.CLKDIV = 10;
  AD0.CR.CLKS = 0;
  AD0.INTEN.ADINTEN = 1;

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
  ISER |= (1<<17 | 1<<24);
  //test
  //ISER |= ~0;
}

void IRQ17(){
    //MR1 interrupt
    TMR16B1.IR.MR1INT = 1;
    AD0.CR.START = 1;
}

void IRQ24(){
    //AD0 interrupt
    //AD0.DR0 has 10 bits of measurement
    //MR0 -> 19500 maximum, 17500 minimum
    //since 2^10 = 1024, try multiplying by 2 and subtracting 48
    //for quick, slightly sloppy estimate

    //it's possible that this underflows, come back
    TMR16B1.MR0 = 19500 - ((AD0.DR0.V_VREF - 24) << 1);
}
