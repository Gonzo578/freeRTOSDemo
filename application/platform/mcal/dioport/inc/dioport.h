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

template <std::size_t N>
constexpr IOPortConfig_t configure_IOPort (const std::array<IOPinConfig,N> pinConfigArray) {
    IOPortConfig_t portCfg = {0};

    for (const auto& pinConfig : pinConfigArray) {
        portCfg.Mode_Reg        += pinConfig.Function   << (pinConfig.PinNumber * 2);
        portCfg.OutputSpeed_Reg += pinConfig.Speed      << (pinConfig.PinNumber * 2);
    }

    return portCfg;
}

void ConfigureIOPort (const IOPortConfig_t port_cfg) {
    IOPortConfig_t  port = port_cfg;
}

}//mcal
