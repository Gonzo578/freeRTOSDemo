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

#include <array>
#include <cstdint>
#include "stm32g4xx.h" // STM32 Header für Registerdefinitionen

namespace mcal {

using IOPinConfig_t = struct IOPinConfig {
    uint32_t PinNumber;
    enum IOFUNCTION     : uint32_t { INPUT = 0, OUTPUT = 1, ALT = 2, ANALOG = 3 } Function;
    enum IOTYPE         : uint32_t { PUSHPULL = 0, OPENDRAIN = 1 } Type;
    enum IOSPEED        : uint32_t { LOW = 0, MEDIUM = 1, HIGH = 2, VERYHIGH = 3 } Speed;
    enum IOPULL         : uint32_t { NONE = 0, PULLUP = 1, PULLDOWN = 2 } Bias;
    enum IOSTATE        : uint32_t { LOGIC_LOW, LOGIC_HIGH, DONT_CARE } InitialState;
    enum ALTFUNCTION    : uint32_t { AF0 = 0, AF1, AF2, AF3, AF4, AF5, AF6, AF7, AF8, AF9, AF10, AF11, AF12, AF13, AF14, AF15 } AltFunc;
};

template <size_t NumPins>
using GPIOPortConfig_t = std::array<IOPinConfig_t, NumPins>;

using GPIOPortRegisterConfig_t = struct GPIOPortRegisterConfig {
    uint32_t mode = 0;
    uint32_t type = 0;
    uint32_t speed = 0;
    uint32_t pull = 0;
    uint32_t alt[2] = {0, 0}; // Alternate function registers (AFRL, AFRH)
    uint32_t odr = 0; // Output data register
};

constexpr uint32_t getModeRegisterValue(const IOPinConfig_t& config) {
    return (config.Function << (config.PinNumber * 2));
}

constexpr uint32_t getTypeRegisterValue(const IOPinConfig_t& config) {
    return (config.Type == IOPinConfig_t::OPENDRAIN) ? (1U << config.PinNumber) : 0U;
}

constexpr uint32_t getSpeedRegisterValue(const IOPinConfig_t& config) {
    return (config.Speed << (config.PinNumber * 2));
}

constexpr uint32_t getPullRegisterValue(const IOPinConfig_t& config) {
    return (config.Bias << (config.PinNumber * 2));
}

constexpr uint32_t getAltFuncRegisterValue(const IOPinConfig_t& config) {
    return (config.AltFunc << ((config.PinNumber % 8) * 4));
}

constexpr uint32_t getOutputDataRegisterValue(const IOPinConfig_t& config) {
    return (config.InitialState == IOPinConfig_t::LOGIC_HIGH) ? (1U << config.PinNumber) : 0U;
}

template <size_t NumPins>
constexpr GPIOPortRegisterConfig_t generateGPIOPortConfig(const GPIOPortConfig_t<NumPins>& portConfig) {
    GPIOPortRegisterConfig_t portRegisterConfig{0};

    for (const auto& pin : portConfig) {
        portRegisterConfig.mode     |= getModeRegisterValue(pin);
        portRegisterConfig.type     |= getTypeRegisterValue(pin);
        portRegisterConfig.speed    |= getSpeedRegisterValue(pin);
        portRegisterConfig.pull     |= getPullRegisterValue(pin);

        if (pin.Function == IOPinConfig_t::ALT) {
            if (pin.PinNumber < 8) {
                portRegisterConfig.alt[0] |= getAltFuncRegisterValue(pin);
            } else {
                portRegisterConfig.alt[1] |= getAltFuncRegisterValue(pin);
            }
        }

        if (pin.Function == IOPinConfig_t::OUTPUT) {
            portRegisterConfig.odr |= getOutputDataRegisterValue(pin);
        }
    }

    return portRegisterConfig;
}

void configureGPIOPort(GPIO_TypeDef* port, const GPIOPortRegisterConfig_t& config) {
    port->MODER     = config.mode;
    port->OTYPER    = config.type;
    port->OSPEEDR   = config.speed;
    port->PUPDR     = config.pull;
    port->AFR[0]    = config.alt[0];
    port->AFR[1]    = config.alt[1];
    port->ODR       = config.odr;
}

} // namespace mcal
