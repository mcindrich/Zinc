#pragma once

#include <cstdint>
#include <vm/Opcode.hpp>

namespace zinc {
namespace vm {
    class Instruction {
    public:
        Instruction();
        Instruction(uint32_t in);
        Opcode getOpcode() const;

    private:
        uint32_t m_instruction;
    };
}
}