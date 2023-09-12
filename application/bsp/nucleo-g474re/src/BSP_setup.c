#include "BSP_setup.h"
#include "stm32g4xx.h"

void BSP_HWSetup(void)  {
	RCC->AHB2ENR  |= RCC_AHB2ENR_GPIOAEN;
    RCC->AHB2ENR  |= RCC_AHB2ENR_GPIOBEN;
    RCC->APB1ENR1 |= RCC_APB1ENR1_I2C1EN;
	GPIOA->MODER   = 0xABFFF7FF;
	GPIOA->ODR    |= 0x00000020;
}
