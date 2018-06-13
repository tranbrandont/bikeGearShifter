#include "lpc1114.h"
#include "stepper.h"
int currMotor = 7;
//state machine
int pendingsteps = 0;
int isReverse = 0;
int on = 0;
__attribute__((constructor)) void setUpStepper(){
    //read the switch on GPIO1_6,make it an input pin.
    SYSCON.SYSAHBCLKCTRL.CT32B0 = 1;
    GPIO1.DIR &= ~(1 << 6);
    GPIO1.IS &= ~(1<<6);
    GPIO1.IEV &= ~(1<<6);
    GPIO1.IE = 1<<6;
    //GPIO1.IBE |= (1<<6);
    IOCON.PIO1_6.MODE = 0x2;


    //make PIO0 1, 2, 3, and 7 output
    GPIO0.DIR |= (1<<1)|(1<<2)|(1<<3)|(1<<7);
    GPIO0.DATA[1<<1] = 0;
    GPIO0.DATA[1<<2] = 0;
    GPIO0.DATA[1<<3] = 0;
    GPIO0.DATA[1<<7] = 0;

    //5 ms timer
    TMR32B0.PR = 48;
    TMR32B0.MR0 = 1000;
    TMR32B0.MR1 = 5000;

    TMR32B0.MCR.MR0I = 1;
    TMR32B0.MCR.MR1I = 1;
    TMR32B0.MCR.MR1R = 0;

    TMR32B0.TC = 0;
    TMR32B0.PC = 0;
}

//steps the motor A-> B -> !A -> !B
void stepUp(int nsteps) {
    isReverse = 0;
    pendingsteps = nsteps;
    on = 1;
    TMR32B0.TCR.CEn = 1;
    while (pendingsteps);
}

//steps A!-> B -> A -> B!
void stepBack(int nsteps) {
    pendingsteps = nsteps;
    isReverse = 1;
    on = 1;
    TMR32B0.TCR.CEn = 1;
    while (pendingsteps);
}
void step(int nsteps){
    if (nsteps < 0){
        stepBack( -1 * nsteps);
    }
    else{
        stepUp(nsteps);
    }
}

void switchPressed(){
    GPIO0.DATA[1<<1] ^= ~0;
    GPIO1.IC = (1<<6);
}

void IRQ18(){
   // GPIO0.DATA[1<<currMotor] ^= (1<<currMotor);
    if (on){
        GPIO0.DATA[1<<currMotor] = (1<<currMotor);
        on = 0;
    }
    else{
        GPIO0.DATA[1<<currMotor] = 0;
        if (isReverse){
            switch (currMotor) {
                case 1: currMotor = 7;
                        break;
                case 2: currMotor = 3;
                        break;
                case 3: currMotor = 1;
                        break;
                case 7: currMotor = 2;
                        break;
            } 
        }else{
            switch (currMotor) {
                case 1: currMotor = 3;
                        break;
                case 2: currMotor = 7;
                        break;
                case 3: currMotor = 2;
                        break;
                case 7: currMotor = 1;
                        break;
            }    }
        on = 1;
        pendingsteps--;
        if (pendingsteps == 0){
            TMR32B0.TCR.CEn = 0;
        }
    }
}
void IRQ30() {
    switchPressed();
}
