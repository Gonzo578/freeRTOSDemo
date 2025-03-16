#pragma once

#include "dioport.h"

extern mcal::OutputPin UserLEDOutputPin;
extern mcal::InputPin  UserButtonInputPin;

void BSP_Setup_MCU(void);
