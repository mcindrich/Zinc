#pragma once

#include <vm/Opcode.hpp>
#include <cstdint>

namespace zinc {
namespace vm {
    class Instruction {
    public:
        static const int INSTRUCTION_BITS = 32;

        Instruction();

        void setOpcode(Opcode val);
        void setR0(uint8_t val);
        void setR1(uint8_t val);
        void setR2(uint8_t val);
        void setExtraBits(uint8_t val);
        void set0RValue(uint32_t val);
        void set1RValue(uint32_t val);
        void set2RValue(uint32_t val);

        Opcode getOpcode() const;
        uint8_t getR0() const;
        uint8_t getR1() const;
        uint8_t getR2() const;
        uint8_t getExtraBits() const;
        uint32_t get0RValue() const;
        uint32_t get1RValue() const;
        uint32_t get2RValue() const;

    private:
        // format:
        // [xxxxxx (OPCODE) = 6 bits][xx (2 extra bits for later improvements)]
        // [xxxx (R0) | xxx...xxx (value - 24 bits)]
        // [xxxx (R1) | xxx...xxx (value - 20 bits)]
        // [xxxx (R2) | xxx...xxx (value - 16 bits)]
        uint32_t m_instruction;
    };
}
}