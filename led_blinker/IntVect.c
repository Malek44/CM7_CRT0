/*
******************************************************************************
**
**  File        : IntVect.c
**
**  Author      : Malek Lamari
**
**  Date        : 18/05/2021
**
**  Abstract    : Basic Interrupt Vector implementation
**
**  Target      : Cortex-M7
**
**  No license, use as you wish, no warranty
**
****************************************************************************
*/

/* Linker sections */
extern unsigned int _estack;

/* Entry point */
extern void core_SysEntry(void);

/* Handlers forward declarations */
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

/* Exception Table */
__attribute__ ((section(".isr_vector")))
const unsigned int intr_vector_table[] = {
	(unsigned int) &_estack,              // SP init value
	(unsigned int) core_SysEntry,         // PC init value
    (unsigned int) NMI_Handler,
    (unsigned int) HardFault_Handler,
    (unsigned int) MemManage_Handler,
    (unsigned int) BusFault_Handler,
    (unsigned int) UsageFault_Handler,
    0,                                     // Reserved
    0,                                     // Reserved
    0,                                     // Reserved
    0,                                     // Reserved
    (unsigned int) SVC_Handler,
    (unsigned int) DebugMon_Handler,
    0,                                     // Reserved
    (unsigned int) PendSV_Handler,
    (unsigned int) SysTick_Handler
};

void NMI_Handler(void) {
    while (1) {}
}

void HardFault_Handler(void) {
    while (1) {}
}

void MemManage_Handler(void)
{
	while (1) {}
}

void BusFault_Handler(void)
{
	while (1) {}
}

void UsageFault_Handler(void)
{
	while (1) {}
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
}
