#pragma once

#include <cstdint>

namespace zinc {
namespace vm {
    class Instruction {
        Instruction();
        Instruction(uint64_t in);

    private:
        uint64_t m_instruction;
    };
}
}