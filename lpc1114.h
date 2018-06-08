#define VU volatile unsigned
#define RES volatile const unsigned
void loop();
void setup();
typedef struct {
    VU FUNC  : 3;
    VU MODE  : 2;
    VU HYS   : 1;
    RES      : 4;
    VU OD    : 1;
    RES      : 21;
} pio_t;
typedef struct {
    VU FUNC  : 3;
    VU MODE  : 2;
    VU HYS   : 1;
    RES      : 1;
    VU ADMODE :1;
    RES      : 2;
    VU OD    : 1;
    RES      : 21;
} r_pio_t;

extern struct{
    pio_t PIO2_6;
    VU : 32;
    pio_t PIO2_0;
    pio_t RESET_PIO0_0;
    pio_t PIO0_1;
    pio_t PIO1_8;
    VU : 32;
    pio_t PIO0_2;
    pio_t PIO2_7;
    pio_t PIO2_8;
    pio_t PIO2_1;
    pio_t PIO0_3;
    struct {
      volatile unsigned FUNC: 3;
      volatile unsigned     : 5;
      volatile unsigned I2CMODE : 2;
      volatile unsigned     : 22;
    } PIO0_4;
    struct {
      volatile unsigned FUNC: 3;
      volatile unsigned     : 5;
      volatile unsigned I2CMODE : 2;
      volatile unsigned     : 22;
    } PIO0_5;
    pio_t PIO1_9;
    pio_t PIO3_4;
    pio_t PIO2_4;
    pio_t PIO2_5;
    pio_t PIO3_5;
    pio_t PIO0_6;
    pio_t PIO0_7;
    pio_t PIO2_9;
    pio_t PIO2_10;
    pio_t PIO2_2;
    pio_t PIO0_8;
    pio_t PIO0_9;
    pio_t SWCLK_PIO0_10;
    pio_t PIO1_10;
    pio_t PIO2_11;
    r_pio_t R_PIO0_11;
    r_pio_t R_PIO1_0;
    r_pio_t R_PIO1_1;
    r_pio_t R_PIO1_2;
    pio_t PIO3_0;
    pio_t PIO3_1;
    pio_t PIO2_3;
    pio_t SWDIO_PIO1_3;
    pio_t PIO1_4;
    pio_t PIO1_11;
    pio_t PIO3_2;
    pio_t PIO1_5;
    pio_t PIO1_6;
    pio_t PIO1_7;
    pio_t PIO3_3;
    struct {
        VU SCKLOC : 2;
        VU        : 30;
    } SCK_LOC;
    struct {
        VU DSRLOC : 2;
        VU        : 30;
    } DSR_LOC;
    struct {
        VU DCDLOC : 2;
        VU        : 30;
    } DCD_LOC;
    struct {
        VU RILOC : 2;
        VU        : 30;
    } RI_LOC;
} IOCON;

extern struct {
    VU SYSMEMREMAP;
    struct {
      volatile unsigned SSP0_RST_N: 1;
      volatile unsigned I2C_RST_N: 1;
      volatile unsigned SSP1_RST_N: 1;
      volatile unsigned CAN_RST_N: 1;
      volatile unsigned  : 28;
    } PRESETCTRL;
    VU SYSPLLCTRL;
    RES SYSPLLSTAT;
    RES __RESERVED_0[4];
    VU SYSOSCCTRL;
    VU WDTOSCCTRL;
    VU IRCCTRL;
    RES __RESERVED_1[1];
    VU SYSRSTSTAT;
    RES __RESERVED_2[3];
    VU SYSPLLCLKSEL;
    VU SYSPLLCLKUEN;
    RES __RESERVED_3[10];
    VU MAINCLKSEL;
    VU MAINCLKUEN;
    VU SYSAHBCLKDIV;
    RES __RESERVED_4[1];
    struct {
        VU SYS : 1;
        VU ROM : 1;
        VU RAM : 1;
        VU FLASHREG : 1;
        VU FLASHARRAY : 1;
        VU I2C : 1;
        VU GPIO : 1;
        VU CT16B0 : 1;
        VU CT16B1 : 1;
        VU CT32B0 : 1;
        VU CT32B1 : 1;
        VU SSP0 : 1;
        VU UART : 1;
        VU ADC : 1;
        RES    : 1;
        VU WDT : 1;
        VU IOCON : 1;
        VU CAN : 1;
        VU SSP1 : 1;
        RES : 13;

    }  SYSAHBCLKCTRL;
    RES __RESERVED_5[4];
    VU SSP0CLKDIV;
    VU UARTCLKDIV;
    VU SSP1CLKDIV;
    RES __RESERVED_6[12];
    VU WDTCLKSEL;
    VU WDTCLKUEN;
    VU WDTCLKDIV;
    RES __RESERVED_7[1];
    VU CLKOUTCLKSEL;
    VU CLKOUTUEN;
    VU CLKOUTCLKDIV;
    VU __RESERVED_8[5];
    RES PIOPORCAP0;
    RES PIOPORCAP1;
    RES __RESERVED_9[18];
    VU BODCTRL;
    VU SYSTCKCAL;
    RES __RESERVED_A[6];
    VU IRQLATENCY;
    VU NMISRC;
    RES __RESERVED_B[34];
    VU STARTAPRP0;
    VU STARTERP0;
    VU STARTRSRP0CLR;
    RES STARTSRP0;
    RES __RESERVED_C[8];
    VU PDSLEEPCFG;
    VU PDAWAKECFG;

    //VU PDRUNCFG;
    struct {
        VU IRCOUT_PD : 1;
        VU IRC_PD : 1;
        VU FLASH_PD : 1;
        VU BOD_PD : 1;
        VU ADC_PD : 1;
        VU SYSOSC_PD : 1;
        VU WDTOSC_PD : 1;
        VU SYSPLL_PD : 1;
        RES : 24;
    } PDRUNCFG;

    RES __RESERVED_D[110];
    RES DEVICE_ID;
} SYSCON;

struct {
    struct {
        VU MR0INT : 1;
        VU MR1INT : 1;
        VU MR2INT : 1;
        VU MR3INT : 1;
        VU CR0INT : 1;
        RES       : 27;
    } IR;
    struct {
        VU CEn  : 1;
        VU CRst : 1;
        RES     : 30;
    } TCR;
    VU TC : 16;
    RES   : 16;
    VU PR : 16;
    RES   : 16;
    VU PC : 16;
    RES   : 16;
    struct {
        VU MR0I : 1;
        VU MR0R : 1;
        VU MR0S : 1;
        VU MR1I : 1;
        VU MR1R : 1;
        VU MR1S : 1;
        VU MR2I : 1;
        VU MR2R : 1;
        VU MR2S : 1;
        VU MR3I : 1;
        VU MR3R : 1;
        VU MR3S : 1;
        RES     : 20;
    } MCR;
    //Documentation for these implies they're structs with a MATCH member
    //Just note this in case future demo code doesn't work
    VU MR0 : 16;
    RES :  16;
    VU MR1 : 16;
    RES :    16;
    VU MR2 : 16;
    RES :  16;
    VU MR3 : 16;
    RES :  16;
    struct{
        VU CAP0RE : 1;
        VU CAP0FE : 1;
        VU CAP0I  : 1;
        RES       : 29;
    } CCR;
    //same, this logically has a CAP member...
    VU CR0 : 16;
    RES : 16;
    //undocumented pad??
    RES : 16;
    RES : 16;
    RES : 16;
    RES : 16;
    RES : 16;
    RES : 16;
    struct{
        VU EM0 : 1;
        VU EM1 : 1;
        VU EM2 : 1;
        VU EM3 : 1;
        VU EMC0 : 1;
        VU EMC1 : 1;
        VU EMC2 : 1;
        VU EMC3 : 1;
        RES : 24;
    } EMR;
    //pad (correct?)
    volatile unsigned __reserved[12];
    struct {
        VU CTM : 2;
        VU CIS : 2;
        RES : 28;
    } CTCR;
    struct{
        VU PWMEN0 : 1;
        VU PWMEN1 : 1;
        VU PWMEN2 : 1;
        VU PWMEN3 : 1;
        RES : 28;
    } PWMC;
} extern TMR16B0, TMR16B1;

typedef struct {
    RES : 6;
    VU V_VREF : 10;
    RES : 14;
    VU OVERRUN : 1;
    VU DONE : 1;
} dr_t;

//Analog-digital converter struct
struct {
    struct {
        VU SEL : 8;
        VU CLKDIV : 8;
        VU BURST : 1;
        VU CLKS : 3;
        RES : 4;
        VU START : 3;
        VU EDGE : 1;
        RES : 4;
    } CR;
    struct {
        RES  : 6;
        VU V_VREF : 10;
        RES : 8;
        VU CHN : 3;
        RES : 3;
        VU OVERRUN : 1;
        VU DONE : 1;
    } GDR;
    RES : 32;
    struct {
        VU ADINTEN : 8;
        VU ADGINTEN : 1;
        RES : 23;
    } INTEN;
    dr_t DR0;
    dr_t DR1;
    dr_t DR2;
    dr_t DR3;
    dr_t DR4;
    dr_t DR5;
    dr_t DR6;
    dr_t DR7;
    struct {
        VU DONE : 8;
        VU OVERRUN : 8;
        VU ADINT : 1;
        RES : 15;
    } STAT;
} extern AD0;
extern unsigned ISER;

struct {
    struct{
        VU ENABLE : 1;
        VU TICKINT : 1;
        VU CLKSOURCE : 1;
        RES : 13;
        VU COUNTFLAG : 1;
        RES : 15;
    } CSR;
    struct{
        VU RELOAD : 24;
        RES : 8;
    } RVR;
    struct{
        VU CURRENT : 24;
        RES : 8;
    } CVR;
    struct{
        VU TENMS : 24;
        RES : 6;
        VU SKEW : 1;
        VU NOREF : 1;
    } CALIB;
} extern SYST;

struct {
    VU DATA[0x1000]; //0xFFF?
    RES res1[0x1000];
    VU DIR;
    VU IS;
    VU IBE;
    VU IEV;
    VU IE;
    VU RIS;
    VU MIS;
    VU IC;
} extern GPIO0, GPIO1;

extern struct {
  VU IR;
  VU TCR;
  VU TC;
  VU PR;
  VU PC;
  struct {
    VU MR0I : 1;
    VU MR0R : 1;
    VU MR0S : 1;
    VU MR1I : 1;
    VU MR1R : 1;
    VU MR1S : 1;
    VU MR2I : 1;
    VU MR2R : 1;
    VU MR2S : 1;
    VU MR3I : 1;
    VU MR3R : 1;
    VU MR3S : 1;
    RES : 20;
  } MCR;
  VU MR0;
  VU MR1;
  VU MR2;
  VU MR3;
  VU CCR;
  VU CR0;
  VU EMR;
  RES __RESERVED_0[12];
  VU CTCR;
  VU PWMC;
} TMR32B0, TMR32B1;

extern struct {
  volatile       unsigned CONSET;
  volatile       unsigned STAT;
  volatile       unsigned DAT;
  volatile       unsigned ADR0;
  volatile       unsigned SCLH;
  volatile       unsigned SCLL;
  volatile       unsigned CONCLR;
  volatile       unsigned MMCTRL;
  volatile       unsigned ADR1;
  volatile       unsigned ADR2;
  volatile       unsigned ADR3;
  volatile       unsigned DATA_BUFFER;
  volatile       unsigned MASK0;
  volatile       unsigned MASK1;
  volatile       unsigned MASK2;
  volatile       unsigned MASK3;
} I2C0;

extern void hallsetup();
