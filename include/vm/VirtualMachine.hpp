#pragma once

#include <vm/CPU.hpp>
#include <vm/Memory.hpp>
#include <vm/Register.hpp>

#define ZINC_VM_REG_COUNT 16

namespace zinc {
namespace vm {
    class VirtualMachine {
    public:
        VirtualMachine();

    private:
        CPU m_cpu;
        Memory m_mem;
        Register m_reg[ZINC_VM_REG_COUNT];
    };
}
}