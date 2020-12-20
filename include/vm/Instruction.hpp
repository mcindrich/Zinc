#pragma once

#include <vm/Opcode.hpp>
#include <cstdint>

namespace zinc {
namespace vm {
    class Instruction {
        Instruction();
        Instruction(uint64_t in);

        void setOpcode(Opcode op);
        void setR0(uint8_t r);
        void setR1(uint8_t r);
        void setR2(uint8_t r);

        Opcode getOpcode() const;
        uint8_t getR0() const;
        uint8_t getR1() const;
        uint8_t getR2() const;

    private:
        uint64_t m_instruction;
    };
}
}