#include "lpc1114.h"

//if you ride this bike for like 1.5 straight years
//have the gears change unexpectedly or something
uint32_t centisec_timer = 0;

//timestamps of the last 12 times we found a new magnet
uint32_t[12] history;
char currsample = 0;

const int ADC_LOW_THRESH = 200;
const int ADC_HI_THRESH = 700;

const int SHIFT_DOWN_THRESH = 75;
const int SHIFT_UP_THRESH = 150;

enum State{
    HI;
    LO;
};
State state = HI;


void setup(){
  //set up systick
  SYST.CSR.CLKSOURCE = 1;
  SYST.RVR.RELOAD = 479999; //interrupts every 10ms
  SYST.CVR.CURRENT = 1;
  SYST.CSR.TICKINT = 1;
  SYST.CSR.ENABLE = 1;

  //set up AD0
  SYSCON.SYSAHBCLKCTRL.ADC = 1;
  SYSCON.SYSAHBCLKCTRL.IOCON  = 1;
  IOCON.R_PIO0_11.FUNC = 2;
  IOCON.R_PIO0_11.ADMODE = 0;
  SYSCON.SYSAHBCLKCTRL.IOCON  = 0;
  AD0.CR.SEL = 1;
  AD0.CR.CLKDIV = 10;
  AD0.CR.CLKS = 0;
  AD0.INTEN.ADINTEN = 1;
}

void startsample(){
    centisec_timer++;
    TMR16B1.IR.MR1INT = 1;
    AD0.CR.START = 1;
}

void handlesample(){
    int result = AD0.DR0.V_VREF;
    if (result > ADC_HI_THRESH){
        state = HI;
    }
    else if (result < ADC_LO_THRESH && state != LO){
        state = LO;
        currsample = (currsample + 1) % 12;
        history[currsample] = centisec_timer;
        char oldest = (currsample == 11)? (0) : (currsample + 1);
        if (centisec_timer < oldest){
            //either we've overflowed (Tour de entire width of France?!) or we
            //haven't gotten 12 samples yet. Don't shift yet
            return;
        }
        if (centisec_timer - oldest > SHIFT_UP_THRESH){
            //wipe history (so we don't shift too quickly)
            for (int i = 0; i < 12; i++){
                history[i] = 0;
            }
            //TODO: shift up
            return;
        }
        if  (centisec_timer - oldest < SHIFT_DOWN_THRESH){
            //wipe history
            for (int i = 0; i < 12; i++){
                history[i] = 0;
            }
            //TODO: shift down
            return;
        }
    }

}

void SysTick(){
    startsample();
}

void IRQ24(){
    handlesample();
}

