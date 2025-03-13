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

#include "IDigitalInput.h"
#include "osal.h"
#include <cstdint>

class DoorTask : public osal::Task {
    public:
        enum class State_t : std::uint8_t {
            UNKNOWN = 0,
            CLOSED = 1,
            OPEN = 2
        };

        DoorTask(IDigitalInput& sensor1_in, IDigitalInput& sensor2_in) : Task("DOOR", 128, 1), DoorSensor_m(sensor1_in), DoorSensor2_m(sensor2_in) {}
    
    private:
        IDigitalInput&  DoorSensor_m;
        IDigitalInput&  DoorSensor2_m;
        State_t         DoorState_m = State_t::UNKNOWN;
        State_t         DoorState2_m = State_t::UNKNOWN;
		
	protected:
    
		void run() override;
};
