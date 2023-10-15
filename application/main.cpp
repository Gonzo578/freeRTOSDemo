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
//#include "stm32g4xx.h"
#include "osal.h"
#include "heartbeat.h"
#include "dio.h"

HeartbeatTask Heatbeat;


constexpr std::array<mcal::IOPinConfig_t, 3>	PortA_Pin_Config = {{
	{0, mcal::IOPinConfig_t::IOFUNCTION::OUTPUT, 0, mcal::IOPinConfig_t::IOTYPE::NORMAL, mcal::IOPinConfig_t::IOSPEED::HIGH, mcal::IOPinConfig_t::IOPULL::NONE, mcal::IOPinConfig_t::IOSTATE::LOGIC_LOW},
	{1, mcal::IOPinConfig_t::IOFUNCTION::OUTPUT, 0, mcal::IOPinConfig_t::IOTYPE::NORMAL, mcal::IOPinConfig_t::IOSPEED::LOW, mcal::IOPinConfig_t::IOPULL::NONE, mcal::IOPinConfig_t::IOSTATE::LOGIC_HIGH},
	{2, mcal::IOPinConfig_t::IOFUNCTION::INPUT,  0, mcal::IOPinConfig_t::IOTYPE::NORMAL, mcal::IOPinConfig_t::IOSPEED::LOW, mcal::IOPinConfig_t::IOPULL::NONE, mcal::IOPinConfig_t::IOSTATE::DONT_CARE}
}};

constexpr auto PortA_Config  = mcal::configure_IOPort (PortA_Pin_Config);

int main(void)
{
	mcal::ConfigureIOPort(PortA_Config);
	BSP_HWSetup();

	// start heartbeat task
	Heatbeat.start();

	/* Start the scheduler. */
	osal::startOS();

	for(;;) {}

	return 0;
}
