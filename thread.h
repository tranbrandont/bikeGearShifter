#if !defined(_d90f27ea_1a86_4e3f_b590_85905e8dae47)
#define _d90f27ea_1a86_4e3f_b590_85905e8dae47


typedef
struct thread_st {
  void*     next;                                                       
  unsigned* sp;                                                         
  unsigned stack[0];
} thread_t;


#define THREAD(name, startfun, stacksize, arg0, arg1, arg2, arg3)       \
  struct {                                                              \
    thread_t  thread;                                                   \
    unsigned  stack[((stacksize)-16)];                                  \
    unsigned  r8;                                                       \
    unsigned  r9;                                                       \
    unsigned  r10;                                                      \
    unsigned  r11;                                                      \
    unsigned  r4;                                                       \
    unsigned  r5;                                                       \
    unsigned  r6;                                                       \
    unsigned  r7;                                                       \
    unsigned  r0;                                                       \
    unsigned  r1;                                                       \
    unsigned  r2;                                                       \
    unsigned  r3;                                                       \
    unsigned  r12;                                                      \
    unsigned  lr;                                                       \
    void    (*pc)();                                                    \
    unsigned  psr;                                                      \
  } static name = {                                                     \
    {(void*)0,                                                          \
     &(name.r8)},                                                       \
    {0},                                                                \
    0,0,0,0,0,0,0,0,                                                    \
    (arg0),                                                             \
    (arg1),                                                             \
    (arg2),                                                             \
    (arg3),                                                             \
    0,                                                                  \
    0,                                                                  \
    startfun,                                                           \
    1<<24};                                                             \
  void* __##name##__ptr __attribute__((section(".threads"))) = &name



#endif //_d90f27ea_1a86_4e3f_b590_85905e8dae47
