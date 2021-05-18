/*
******************************************************************************
**
**  File        : main.c
**
**  Author      : Malek Lamari
**
**  Date        : 18/05/2021
**
**  Abstract    : Baremetal LED blinker using CM7_CRT0 bootstrap
**
**  Target      : Cortex-M7
**
**  No license, use as you wish, no warranty
**
****************************************************************************
*/

#define GPIOB_EN_BIT        2
#define LED1_GPIO_PIN_MSK   1 //PIN0
#define LED1_MODE_OUT       1

#define RCC_BASE        0x58024400UL
#define RCC_AHB4ENR     *((volatile unsigned int *) 0x580244E0UL)

#define GPIOB_BASE      0x58020400UL
#define GPIOB_MODER     *((volatile unsigned int *) 0x58020400UL)
#define GPIOB_ODR       *((volatile unsigned int *) 0x58020414UL)


int main(void)
{
	//Enable GPIOB clock
	RCC_AHB4ENR |= GPIOB_EN_BIT;

	//Set PIN0 at GPIOB as output
	GPIOB_MODER = (GPIOB_MODER & (~3)) | LED1_MODE_OUT;

	//Infinite loop
	while(1)
	{
		GPIOB_ODR |= LED1_GPIO_PIN_MSK;
		for (int i = 0; i < 1000000; i++); //some delay
		GPIOB_ODR &= ~LED1_GPIO_PIN_MSK;
		for (int i = 0; i < 1000000; i++); //some delay
	}
}
