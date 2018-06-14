#include "lpc1114.h"
#include "thread.h"
#include "hall.h"
#include "servo.h"
#include "stepper.h"

void setup() __attribute__((weak));
void loop()  __attribute__((weak));
void reset();

void reset() {
  SYSCON.MAINCLKSEL = 0;
  SYSCON.MAINCLKUEN = 0;
  SYSCON.MAINCLKUEN = 1;
  SYSCON.SYSPLLCTRL = 0x23;
  SYSCON.SYSPLLCLKSEL = 0;
  SYSCON.SYSPLLCLKUEN = 0;
  SYSCON.SYSPLLCLKUEN = 1;
  *((unsigned*)(&SYSCON.PDRUNCFG)) &= ~(1<<7);

  while(SYSCON.SYSPLLSTAT == 0) {}

  SYSCON.MAINCLKSEL = 0x3;
  SYSCON.MAINCLKUEN = 0;
  SYSCON.MAINCLKUEN = 1;
  SYST.CSR.ENABLE = 1;
  

  home();
  setservopos(0);


  if(setup) {
    setup();
  }

  if(loop) {
    while(1)
      loop();
  }
  else {
    while(1)
      __asm("wfi");
  }

}
