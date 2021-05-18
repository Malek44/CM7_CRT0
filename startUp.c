/*
******************************************************************************
**
**  File        : startUp.c
**
**  Author      : Malek Lamari
**
**  Date        : 18/05/2021
**
**  Abstract    : Basic CRT0 like bootstrap implementation
**
**  Target      : Cortex-M7
**
**  No license, use as you wish, no warranty
**
****************************************************************************
*/


/* Linker sections */
extern unsigned int _etext;
extern unsigned int _sbss;
extern unsigned int _ebss;
extern unsigned int _sdata;
extern unsigned int _edata;

/* ROM region */
#define ROM_DATA_SECTION_BASE (unsigned int)&_etext
#define ROM_DATA_SECTION_SIZE (unsigned int)(&_edata - &_sdata)

/* RAM region */
#define RAM_DATA_SECTION_BASE (unsigned int)&_sdata

/* BSS region */
#define BSS_SECTION_BASE (unsigned int)&_sbss
#define BSS_SECTION_SIZE (unsigned int)(&_ebss - &_sbss)

#define ENABLE_IT asm("CPSIE I")

/* Extern functions */
int main(void) __attribute__ ((weak));

/* Static functions declaration */
void core_SysEntry(void);
static void core_MemCpy(unsigned char *dest, const unsigned char *src, unsigned int size);
static void core_MemSet(unsigned char *ptr, unsigned char value, unsigned int length);
static void core_CallUserCode(void);
static void core_InitRam(void);
static void core_InitClock(void);
static void core_UnexpectedExit(void);


/* Static functions definition */
void core_SysEntry(void)
{
	/* Configure System Clock */
	core_InitClock();

	/* Copy data section and init bss section */
	core_InitRam();

	/* Jump to user code */
	core_CallUserCode();
}

static void core_MemCpy(unsigned char *dest, const unsigned char *src, unsigned int size)
{
	for(int i=0; i<size; ++i)
	{
		*(dest+i) = *(src+i);
	}
}

static void core_MemSet(unsigned char *ptr, unsigned char value, unsigned int length)
{
	while(length--)
	{
		*ptr++ = value;
	}
}

static void core_CallUserCode(void)
{
	/* Enable interrupts */
	ENABLE_IT;

	/* Call the user main function */
	(void) main();

	/* Handle the case when main() unexpectedly exits */
	core_UnexpectedExit();
}

static void core_InitRam(void)
{
	/* Copy .data section into RAM */
	core_MemCpy((unsigned char*) RAM_DATA_SECTION_BASE, (const unsigned char*) ROM_DATA_SECTION_BASE, ROM_DATA_SECTION_SIZE);

	/* Init .bss section */
	core_MemSet((unsigned char*)BSS_SECTION_BASE, 0, BSS_SECTION_SIZE);
}

static void core_InitClock(void)
{
	/* Using 24 MHz from PLL as system clock */
	#define RCC_BASE        0x58024400UL
	#define RCC_CR          (*((volatile unsigned int *)(RCC_BASE + 0x00UL)))
	#define RCC_CFGR        (*((volatile unsigned int *)(RCC_BASE + 0x10UL)))
	#define RCC_D1CFGR      (*((volatile unsigned int *)(RCC_BASE + 0x18UL)))
	#define RCC_D2CFGR      (*((volatile unsigned int *)(RCC_BASE + 0x1CUL)))
	#define RCC_D3CFGR      (*((volatile unsigned int *)(RCC_BASE + 0x20UL)))
	#define RCC_PLLCKSELR   (*((volatile unsigned int *)(RCC_BASE + 0x28UL)))
	#define RCC_PLLCFGR     (*((volatile unsigned int *)(RCC_BASE + 0x2CUL)))
	#define RCC_PLL1DIVR    (*((volatile unsigned int *)(RCC_BASE + 0x30UL)))
	#define RCC_PLL1FRACR   (*((volatile unsigned int *)(RCC_BASE + 0x34UL)))
	#define RCC_PLL2DIVR    (*((volatile unsigned int *)(RCC_BASE + 0x38UL)))
	#define RCC_PLL2FRACR   (*((volatile unsigned int *)(RCC_BASE + 0x3CUL)))
	#define RCC_PLL3DIVR    (*((volatile unsigned int *)(RCC_BASE + 0x40UL)))
	#define RCC_PLL3FRACR   (*((volatile unsigned int *)(RCC_BASE + 0x44UL)))
	#define RCC_CIER        (*((volatile unsigned int *)(RCC_BASE + 0x60UL)))

	/* Set HSION bit */
	RCC_CR |= 1;

	/* Reset CFGR register */
	RCC_CFGR = 0x00000000;

	/* Reset HSEON, CSSON , CSION,RC48ON, CSIKERON PLL1ON, PLL2ON and PLL3ON bits */
	RCC_CR &= 0xEAF6ED7FU;

	/* Reset D1CFGR register */
	RCC_D1CFGR = 0x00000000;

	/* Reset D2CFGR register */
	RCC_D2CFGR = 0x00000000;

	/* Reset D3CFGR register */
	RCC_D3CFGR = 0x00000000;

	/* Reset PLLCKSELR register */
	RCC_PLLCKSELR = 0x00000000;

	/* Reset PLLCFGR register */
	RCC_PLLCFGR = 0x00000000;

	/* Reset PLL1DIVR register */
	RCC_PLL1DIVR = 0x00000000;

	/* Reset PLL1FRACR register */
	RCC_PLL1FRACR = 0x00000000;

	/* Reset PLL2DIVR register */
	RCC_PLL2DIVR = 0x00000000;

	/* Reset PLL2FRACR register */
	RCC_PLL2FRACR = 0x00000000;

	/* Reset PLL3DIVR register */
	RCC_PLL3DIVR = 0x00000000;

	/* Reset PLL3FRACR register */
	RCC_PLL3FRACR = 0x00000000;

	/* Reset HSEBYP bit */
	RCC_CR &= 0xFFFBFFFFU;

	/* Disable all interrupts */
	RCC_CIER = 0x00000000;
}

static void core_UnexpectedExit(void)
{
	for(;;);
}
