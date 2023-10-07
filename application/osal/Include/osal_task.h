#pragma once

#include "FreeRTOS.h"
#include "task.h"

namespace osal {

class RTOSTask {
private:
    TaskHandle_t taskHandle;
    const char* taskName;
    uint32_t stackSize;
    UBaseType_t priority;

    static void taskFunction(void* pvParameters) {
        RTOSTask* taskInstance = static_cast<RTOSTask*>(pvParameters);
        taskInstance->run();
        vTaskDelete(NULL);  // Delete the task when done
    }

protected:
    virtual void run() = 0;

public:
    RTOSTask(const char* name, uint32_t stackSize, UBaseType_t priority)
        : taskHandle(NULL), taskName(name), stackSize(stackSize), priority(priority) {}

    void start() {
        xTaskCreate(taskFunction, taskName, stackSize, this, priority, &taskHandle);
    }

    void stop() {
        if (taskHandle != NULL) {
            vTaskDelete(taskHandle);
            taskHandle = NULL;
        }
    }

    void suspend() {
        vTaskSuspend(taskHandle);
    }

    void resume() {
        vTaskResume(taskHandle);
    }

    ~RTOSTask() {
        stop();
    }
};

}
