#include "lpc1114.h"
#include "thread.h"

void loop_1();
void loop_2();
void loop_3();

THREAD(one, loop_1, 64, 1000000, 0, 0, 0);
THREAD(two, loop_2, 64,  660000, 0, 0, 0);
THREAD(three, loop_3, 64,  830000, 0, 0, 0);


extern void* CURCTX;

/* Setup
 * GPIO0 1, 2, and 3 as output and zero.
 * GPIO0_1 (physical pin 24)  Loop 1's LED
 * GPIO0_2 (physical pin 25)  Loop 2's LED
 * GPIO0_3 (physical pin 26)  Hard Fault's LED
 *   --Since I already have a hardfault LED wired to 1_6, I'll just use it
 */
void setup() {
  SYSCON.SYSAHBCLKCTRL.IOCON=1;
  SYSCON.SYSAHBCLKCTRL.GPIO=1;

  GPIO0.DIR |= (1<<1)|(1<<2)|(1<<3);
  GPIO1.DIR |= (1<<6);
  GPIO0.DATA[1<<1] = 0;
  GPIO0.DATA[1<<2] = 0;
  GPIO0.DATA[1<<3] = 0;
  GPIO1.DATA[1<<6] = 0;

  //set up systick
  SYST.CSR.CLKSOURCE = 1;
  SYST.RVR.RELOAD = 479999;
  SYST.CVR.CURRENT = 1;
  SYST.CSR.TICKINT = 1;
  SYST.CSR.ENABLE = 1;
}


/* Loop 1 (aka, thread 1)
 */
void loop_1(int DELAY) {
  while(1) {
    GPIO0.DATA[1<<1] ^= ~0;
    for(int i = 0; i < DELAY; ++i) {}
  }
}

/* Loop 2 (aka, thread 2)
 */
void loop_2(int DELAY) {
  while(1) {
    GPIO0.DATA[1<<2] ^= ~0;
    for(int i = 0; i < DELAY; ++i) {}
  }
}
/* Loop 3 (aka, thread 3)
 */
void loop_3(int DELAY) {
  while(1) {
    GPIO0.DATA[1<<3] ^= ~0;
    for(int i = 0; i < DELAY; ++i) {}
  }
}
/* HardFault
 * This is really here to tell you that something went wrong with your
 * scheduler.  If you attached GDB and end up here, take a look at the program
 * stack (psp) with gdb.  Since this is an exception, sp is actually msp not
 * psp.
 */
void HardFault () {
  SYSCON.SYSAHBCLKCTRL.IOCON=1;
  SYSCON.SYSAHBCLKCTRL.GPIO=1;
  GPIO1.DIR |= (1<<6);
  GPIO1.DATA[1<<6] = ~0;
  while(1)
    __asm("wfi");
}

