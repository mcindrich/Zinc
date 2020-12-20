#pragma once

#include <array>
#include <vm/Instruction.hpp>
#include <vm/Object.hpp>
#include <list>

#define REG_COUNT 32

namespace zinc {
namespace vm {
    class VirtualMachine {
    public:
        VirtualMachine();

        void execute(std::list<Instruction> &in);

    private:
        // vm specific stuff
        std::list<Instruction> m_instructions;
        Object m_registers[REG_COUNT];
    };
}
}