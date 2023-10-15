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

#include <cstdint>
#include <array>

namespace mcal {

using device_register = uint32_t volatile;      ///< 32bit device / peripheral register

using GPIO_Port_t = struct GPIOPortRegsiterSet {
    device_register MODER;       /*!< GPIO port mode register,               Address offset: 0x00      */
    device_register OTYPER;      /*!< GPIO port output type register,        Address offset: 0x04      */
    device_register OSPEEDR;     /*!< GPIO port output speed register,       Address offset: 0x08      */
    device_register PUPDR;       /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
    device_register IDR;         /*!< GPIO port input data register,         Address offset: 0x10      */
    device_register ODR;         /*!< GPIO port output data register,        Address offset: 0x14      */
    device_register BSRR;        /*!< GPIO port bit set/reset  register,     Address offset: 0x18      */
    device_register LCKR;        /*!< GPIO port configuration lock register, Address offset: 0x1C      */
    device_register AFR[2];      /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
    device_register BRR;         /*!< GPIO Bit Reset register,               Address offset: 0x28      */
};
static_assert(sizeof(GPIO_Port_t) == (11*sizeof(device_register)), "GPIO_Port_t cointains extra padding bytes!\n");

static GPIO_Port_t& GPIOA = *reinterpret_cast<GPIO_Port_t*>(0x48000000);
static GPIO_Port_t& GPIOB = *reinterpret_cast<GPIO_Port_t*>(0x48000400);
static GPIO_Port_t& GPIOC = *reinterpret_cast<GPIO_Port_t*>(0x48000800);
static GPIO_Port_t& GPIOD = *reinterpret_cast<GPIO_Port_t*>(0x48000C00);
static GPIO_Port_t& GPIOE = *reinterpret_cast<GPIO_Port_t*>(0x48001000);
static GPIO_Port_t& GPIOF = *reinterpret_cast<GPIO_Port_t*>(0x48001400);
static GPIO_Port_t& GPIOG = *reinterpret_cast<GPIO_Port_t*>(0x48001800);

using IOPortConfig_t = struct IOPortConfig {
    uint32_t    Mode_Reg;
    uint32_t    OutputType_Reg;
    uint32_t    OutputSpeed_Reg;
    uint32_t    PullUpDown_Reg;
    uint32_t    InitialOutput_Reg;
    uint32_t    AltFunctionL_Reg;
    uint32_t    AltFunctionH_Reg;
};

using IOPinConfig_t = struct  IOPinConfig {
    uint32_t    PinNumber;
    enum IOFUNCTION:uint32_t    { INPUT = 0, OUTPUT = 1, ALT = 2, ANALOG = 3 } Function;
    uint32_t AltFunc;
    enum IOTYPE:uint32_t        { NORMAL = 0, OPENDRAIN = 1 } Type;
    enum IOSPEED:uint32_t       { LOW = 0, MEDIUM = 1, HIGH = 2, VERYHIGH = 3 } Speed;
    enum IOPULL:uint32_t        { NONE = 0, PULLUP = 1, PULLDOWN = 2 } Bias;
    enum IOSTATE:uint32_t       { LOGIC_LOW, LOGIC_HIGH, DONT_CARE } InitialState;
};

template <size_t N>
constexpr IOPortConfig_t configure_IOPort (const std::array<IOPinConfig,N> pinConfigArray) {
    IOPortConfig_t portCfg = {0};

    for (const auto& pinConfig : pinConfigArray) {
        portCfg.Mode_Reg += pinConfig.Function << (pinConfig.PinNumber * 2);
    }

    return portCfg;
}

void ConfigureIOPort (const IOPortConfig_t port_cfg) {
    static IOPortConfig_t  port = port_cfg;
}

class IDioPin {
public:
    enum Pin_t {Pin0 = 0, Pin1, Pin2, Pin3, Pin4, Pin5, Pin6, Pin7, Pin8, Pin9, Pin10, Pin11, Pin12, Pin13, Pin14, Pin15};
    
    enum class PinState_t {
        RESET   = 0,
        SET     = 1
    };

    virtual ~IDioPin(void) = default;

    virtual void set(void) = 0;
    virtual void reset(void) = 0;
    virtual PinState_t read(void) = 0;
};

class DioPin final : public IDioPin {
public:
    DioPin(GPIO_Port_t& port, Pin_t pin) :
                    _port{port},
                    _pin{pin} {

    }

    ~DioPin(void) = default;

    void set (void) override {
        _port.BSRR = (0x00000001 << _pin);
    }

    void reset (void) override {
        _port.BSRR = (0x00010000 << _pin);
    }

    PinState_t read (void) override {
        if(_port.ODR & (0x00000001 << _pin)) {
            return (PinState_t::SET);
        } else {
            return (PinState_t::RESET);
        }
    }

private:
    mcal::GPIO_Port_t& _port;
    Pin_t              _pin;
};

}   // namespace mcal
