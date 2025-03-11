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

#include "stm32g4xx.h" // MCU register definition
#include <cstdint>

namespace mcal
{
    enum Pin_No : uint32_t
    {
        Pin_0 = 0,
        Pin_1,
        Pin_2,
        Pin_3,
        Pin_4,
        Pin_5,
        Pin_6,
        Pin_7,
        Pin_8,
        Pin_9,
        Pin_10,
        Pin_11,
        Pin_12,
        Pin_13,
        Pin_14,
        Pin_15
    };

    using Pin_No_t = Pin_No;

    class OutputPin final
    {
    public:
        OutputPin(GPIO_TypeDef* const port, const Pin_No_t pinNo) : port_m(port),pinNo_m(pinNo) {}

        inline bool isHigh() const
        {
            return ((port_m->ODR & (1UL << pinNo_m)) != 0);
        }

        inline void setHigh() const
        {
            port_m->BSRR = (1 << pinNo_m);
        }

        inline void setLow() const
        {
            port_m->BSRR = (1UL << (pinNo_m + 16));
        }

        inline void toggle() const
        {
            if(isHigh())
                // Set pin low
                setLow();
            else {
                // Set pin high
                setHigh();
            }
        }
    private:
        GPIO_TypeDef* const port_m;
        const Pin_No_t pinNo_m;
    };
} // namespace mcal
