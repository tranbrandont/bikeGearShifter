#include "thread.h"
void reset();
extern thread_t* __THREADS;

THREAD(__main__, reset, 64, 0, 0, 0, 0);

/* This is a cheat to make it easier to find the main stack */
char* const __PSP = ((char*)&__main__)+(sizeof(__main__));

/* Current Running Thread */

thread_t* runlist = 0;
thread_t* runlist_tail = 0;
thread_t* CURCTX= (thread_t*)(&__main__);
thread_t* IDLE = (thread_t*)(&__main__);

void schedule(){
    if(CURCTX){
        if (runlist != 0){ //if runlist empty, keep going
            if(CURCTX != IDLE){
                //enqueue curctx if it isn't the idle thd
                runlist_tail->next = CURCTX;
                runlist_tail = runlist_tail->next;
                CURCTX->next = 0;
            }
                //pop an element
                CURCTX = runlist;
                runlist = runlist->next;
        }
    }
    else{
        if (runlist == 0){
            CURCTX = IDLE;
        }
        else{
            //pop an element
            CURCTX = runlist;
            runlist = runlist->next;
        }
    }
}

////This is important if we actually use the scheduler, which we aren't using here
// void SysTick(){
//     schedule();
// }

__attribute__((constructor)) void thd_ctor(){
    thread_t** thds = &__THREADS;
    int i = 0;
    while (thds[i] != 0){
        thread_t* thd = thds[i];
        i++;
        if(thd != IDLE){
            if (runlist_tail == 0){
                runlist = thd;
                runlist_tail = thd;
            }
            else{
                runlist_tail->next = thd;
                runlist_tail = thd;
                runlist_tail->next = 0;
            }
        }
    }
}
