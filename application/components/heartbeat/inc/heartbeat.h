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

#pragma once

#include "osal_task.h"
#include "stm32g4xx.h"
#include <cstdint>

#define Heartbeat_TASK_PRIORITY				( tskIDLE_PRIORITY + 1UL )

class HeartbeatTask : public osal::Task {
	private:
		std::uint32_t	heartbeatCounter = 0;
	protected:
    
		void run() override {
        	while (1) {
            	heartbeatCounter++;
				vTaskDelay(800);
				GPIOA->BSRR    |= 0x00000020;
				vTaskDelay(200);
				GPIOA->BSRR    |= 0x00200000;
        	}
    	}

public:
    HeartbeatTask() : Task("BEAT", configMINIMAL_STACK_SIZE, Heartbeat_TASK_PRIORITY) {}
};
