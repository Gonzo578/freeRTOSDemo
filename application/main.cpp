// MIT License

// Copyright (c) 2023 Ralf Hochhausen

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <cstdint>
#include <array>
#include "BSP_setup.h"
#include "osal.h"
#include "heartbeat.h"
#include "HighActiveOutput.h"
#include "dioport.h"

const mcal::GPIOPortConfig_t<3> GPIOAPortConfig = {{
    {1, mcal::IOPinConfig_t::OUTPUT, 	mcal::IOPinConfig_t::AF0, mcal::IOPinConfig_t::NORMAL, 		mcal::IOPinConfig_t::HIGH, 		mcal::IOPinConfig_t::PULLUP, 	mcal::IOPinConfig_t::LOGIC_HIGH},
    {2, mcal::IOPinConfig_t::INPUT,  	mcal::IOPinConfig_t::AF1, mcal::IOPinConfig_t::OPENDRAIN, 	mcal::IOPinConfig_t::MEDIUM, 	mcal::IOPinConfig_t::PULLDOWN, 	mcal::IOPinConfig_t::LOGIC_LOW},
    {3, mcal::IOPinConfig_t::ALT, 		mcal::IOPinConfig_t::AF2, mcal::IOPinConfig_t::NORMAL, 		mcal::IOPinConfig_t::VERYHIGH, 	mcal::IOPinConfig_t::NONE, 		mcal::IOPinConfig_t::DONT_CARE}
}};

constexpr auto GPIOA_RegisterConfig = mcal::generateGPIOPortConfig(GPIOAPortConfig);

HighActiveOutput Led1;
HeartbeatTask Heartbeat(Led1);

int main(void)
{
	BSP_HWSetup();

	Heartbeat.start();

	/* Start the scheduler. */
	osal::startOS();

	for(;;) {}

	return 0;
}
