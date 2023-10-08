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

#include "osal.h"
#include "FreeRTOS.h"
#include "task.h"

namespace osal {

    void startOS(void) {
        vTaskStartScheduler();
    }

    void Task::taskFunction(void* pvParameters) {
        Task* taskInstance = static_cast<osal::Task*>(pvParameters);
        taskInstance->run();
        vTaskDelete(NULL);  // Delete the task when done
    }

    Task::Task(const char* name, uint32_t stackSize, UBaseType_t priority)
        : taskHandle(nullptr), taskName(name), stackSize(stackSize), priority(priority) {}

    void Task::start() {
        xTaskCreate(taskFunction, taskName, stackSize, this, priority, static_cast<TaskHandle_t*>(taskHandle));
    }

    void Task::stop() {
        if (taskHandle != NULL) {
            vTaskDelete(static_cast<TaskHandle_t>(taskHandle));
            taskHandle = NULL;
        }
    }

    void Task::suspend() {
        vTaskSuspend(static_cast<TaskHandle_t>(taskHandle));
    }

    void Task::resume() {
        vTaskResume(static_cast<TaskHandle_t>(taskHandle));
    }

    void Task::delay(const uint32_t ticks) {
        vTaskDelay(ticks);
    }

    Task::~Task() {
        stop();
    }
}
