#pragma once

#include <array>
#include <vm/Instruction.hpp>
#include <vm/Object.hpp>
#include <list>

#define REG_COUNT 16

namespace zinc {
namespace vm {
    class VirtualMachine {
    public:
        VirtualMachine();

        void execute(std::vector<Instruction> &in);

    private:
        // vm specific stuff
        std::vector<Instruction> m_instructions;
        Object m_registers[REG_COUNT];
    };
}
}