#pragma once

#include <bits/stdint-uintn.h>
#include "Opcode.h"

namespace zinc {
namespace vm {
    class Instruction {
    public:
        Instruction();

        static const int length = 64;

        void setOpcode(Opcode val);
        Opcode getOpcode() const;

    private:
        uint64_t m_instruction;
    };
}
}