extern void* __INITIAL_SP;
extern void* __VECTOR_CHECKSUM;

#define WEAK __attribute__((weak))
#define WEAKALIAS __attribute__((weak, alias("__default_handler")));
void __reset();
void NMI() WEAKALIAS;
void HardFault() WEAKALIAS;
void SVCall() WEAK;
void PendSV() WEAK;
void SysTick() WEAK;
void IRQ0() WEAK;
void IRQ1() WEAK;
void IRQ2() WEAK;
void IRQ3() WEAK;
void IRQ4() WEAK;
void IRQ5() WEAK;
void IRQ6() WEAK;
void IRQ7() WEAK;
void IRQ8() WEAK;
void IRQ9() WEAK;
void IRQ10() WEAK;
void IRQ11() WEAK;
void IRQ12() WEAK;
void IRQ13() WEAK;
void IRQ14() WEAK;
void IRQ15() WEAK;
void IRQ16() WEAK;
void IRQ17() WEAK;
void IRQ18() WEAK;
void IRQ19() WEAK;
void IRQ20() WEAK;
void IRQ21() WEAK;
void IRQ22() WEAK;
void IRQ23() WEAK;
void IRQ24() WEAK;
void IRQ25() WEAK;
void IRQ26() WEAK;
void IRQ27() WEAK;
void IRQ28() WEAK;
void IRQ29() WEAK;
void IRQ30() WEAK;
void IRQ31() WEAK;
void IRQ32() WEAK;


void __irq_generic ();
unsigned vector[48] __attribute__((section(".vector")))
  = {
  (unsigned)(&__INITIAL_SP),
  (unsigned)(&__reset) + 1,
  (unsigned)(&NMI) + 1,
  (unsigned)(&HardFault) + 1,
  (unsigned)(0x00000000),
  (unsigned)(0x00000000),
  (unsigned)(0x00000000),
  (unsigned)(&__VECTOR_CHECKSUM),
  (unsigned)(0x00000000),
  (unsigned)(0x00000000),
  (unsigned)(0x00000000),
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(0x00000000),
  (unsigned)(0x00000000),
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1,
  (unsigned)(&__irq_generic) + 1
};




typedef void (*irq_t)();
const irq_t __irq_handlers[48] = {
  0,
  0,
  &NMI,
  &HardFault,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  &SVCall,
  0,
  0,
  &PendSV,
  &SysTick,
  &IRQ0,
  &IRQ1,
  &IRQ2,
  &IRQ3,
  &IRQ4,
  &IRQ5,
  &IRQ6,
  &IRQ7,
  &IRQ8,
  &IRQ9,
  &IRQ10,
  &IRQ11,
  &IRQ12,
  &IRQ13,
  &IRQ14,
  &IRQ15,
  &IRQ16,
  &IRQ17,
  &IRQ18,
  &IRQ19,
  &IRQ20,
  &IRQ21,
  &IRQ22,
  &IRQ23,
  &IRQ24,
  &IRQ25,
  &IRQ26,
  &IRQ27,
  &IRQ28,
  &IRQ29,
  &IRQ30,
  &IRQ31
};

void __default_handler() {
}
