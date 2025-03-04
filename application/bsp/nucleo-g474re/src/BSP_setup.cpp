#include "BSP_setup.h"
#include "stm32g4xx.h"
#include "dioport.h"

#include "dioport.h"
#include "dioport.h"

const mcal::GPIOPortConfig_t<16> GPIOAPortConfig = {{
    {0,  mcal::IOPinConfig_t::ANALOG, 	mcal::IOPinConfig_t::PUSHPULL, 	mcal::IOPinConfig_t::LOW, 		mcal::IOPinConfig_t::NONE, 	    mcal::IOPinConfig_t::DONT_CARE,     mcal::IOPinConfig_t::AF0},
    {1,  mcal::IOPinConfig_t::ANALOG, 	mcal::IOPinConfig_t::PUSHPULL, 	mcal::IOPinConfig_t::LOW, 		mcal::IOPinConfig_t::NONE, 	    mcal::IOPinConfig_t::DONT_CARE,     mcal::IOPinConfig_t::AF0},
    {2,  mcal::IOPinConfig_t::ANALOG, 	mcal::IOPinConfig_t::PUSHPULL, 	mcal::IOPinConfig_t::LOW, 		mcal::IOPinConfig_t::NONE, 	    mcal::IOPinConfig_t::DONT_CARE,     mcal::IOPinConfig_t::AF0},
    {3,  mcal::IOPinConfig_t::ANALOG, 	mcal::IOPinConfig_t::PUSHPULL, 	mcal::IOPinConfig_t::LOW, 		mcal::IOPinConfig_t::NONE, 	    mcal::IOPinConfig_t::DONT_CARE,     mcal::IOPinConfig_t::AF0},
    {4,  mcal::IOPinConfig_t::ANALOG, 	mcal::IOPinConfig_t::PUSHPULL, 	mcal::IOPinConfig_t::LOW, 		mcal::IOPinConfig_t::NONE, 	    mcal::IOPinConfig_t::DONT_CARE,     mcal::IOPinConfig_t::AF0},
    {5,  mcal::IOPinConfig_t::OUTPUT, 	mcal::IOPinConfig_t::PUSHPULL, 	mcal::IOPinConfig_t::LOW, 		mcal::IOPinConfig_t::NONE, 	    mcal::IOPinConfig_t::LOGIC_HIGH,    mcal::IOPinConfig_t::AF0},
    {6,  mcal::IOPinConfig_t::ANALOG, 	mcal::IOPinConfig_t::PUSHPULL, 	mcal::IOPinConfig_t::LOW, 		mcal::IOPinConfig_t::NONE, 	    mcal::IOPinConfig_t::DONT_CARE,     mcal::IOPinConfig_t::AF0},
    {7,  mcal::IOPinConfig_t::ANALOG, 	mcal::IOPinConfig_t::PUSHPULL, 	mcal::IOPinConfig_t::LOW, 		mcal::IOPinConfig_t::NONE, 	    mcal::IOPinConfig_t::DONT_CARE,     mcal::IOPinConfig_t::AF0},
    {8,  mcal::IOPinConfig_t::ANALOG, 	mcal::IOPinConfig_t::PUSHPULL, 	mcal::IOPinConfig_t::LOW, 		mcal::IOPinConfig_t::NONE, 	    mcal::IOPinConfig_t::DONT_CARE,     mcal::IOPinConfig_t::AF0},
    {9,  mcal::IOPinConfig_t::ANALOG, 	mcal::IOPinConfig_t::PUSHPULL, 	mcal::IOPinConfig_t::LOW, 		mcal::IOPinConfig_t::NONE, 	    mcal::IOPinConfig_t::DONT_CARE,     mcal::IOPinConfig_t::AF0},
    {10, mcal::IOPinConfig_t::ANALOG, 	mcal::IOPinConfig_t::PUSHPULL, 	mcal::IOPinConfig_t::LOW, 		mcal::IOPinConfig_t::NONE, 	    mcal::IOPinConfig_t::DONT_CARE,     mcal::IOPinConfig_t::AF0},
    {11, mcal::IOPinConfig_t::ANALOG, 	mcal::IOPinConfig_t::PUSHPULL, 	mcal::IOPinConfig_t::LOW, 		mcal::IOPinConfig_t::NONE, 	    mcal::IOPinConfig_t::DONT_CARE,     mcal::IOPinConfig_t::AF0},
    {12, mcal::IOPinConfig_t::ANALOG, 	mcal::IOPinConfig_t::PUSHPULL, 	mcal::IOPinConfig_t::LOW, 		mcal::IOPinConfig_t::NONE, 	    mcal::IOPinConfig_t::DONT_CARE,     mcal::IOPinConfig_t::AF0},
    {13, mcal::IOPinConfig_t::ALT, 	    mcal::IOPinConfig_t::PUSHPULL, 	mcal::IOPinConfig_t::VERYHIGH,  mcal::IOPinConfig_t::PULLUP, 	mcal::IOPinConfig_t::DONT_CARE,     mcal::IOPinConfig_t::AF0},
    {14, mcal::IOPinConfig_t::ALT, 	    mcal::IOPinConfig_t::PUSHPULL, 	mcal::IOPinConfig_t::LOW, 		mcal::IOPinConfig_t::PULLDOWN, 	mcal::IOPinConfig_t::DONT_CARE,     mcal::IOPinConfig_t::AF0},
    {15, mcal::IOPinConfig_t::ALT, 	    mcal::IOPinConfig_t::PUSHPULL, 	mcal::IOPinConfig_t::LOW, 		mcal::IOPinConfig_t::PULLUP, 	mcal::IOPinConfig_t::DONT_CARE,     mcal::IOPinConfig_t::AF0}
}};

constexpr auto GPIOA_RegisterConfig = mcal::generateGPIOPortConfig(GPIOAPortConfig);

void BSP_HWSetup(void)  {
	RCC->AHB2ENR  |= RCC_AHB2ENR_GPIOAEN;
    RCC->AHB2ENR  |= RCC_AHB2ENR_GPIOBEN;
    RCC->APB1ENR1 |= RCC_APB1ENR1_I2C1EN;
    
	configureGPIOPort(GPIOA, GPIOA_RegisterConfig);
}
