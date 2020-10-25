#pragma once

#include <vm/CPU.hpp>
#include <vm/Memory.hpp>
#include <vm/Register.hpp>
#include <vm/Instruction.hpp>
#include <list>

#define KByte 1024
#define MByte 1024 * KByte
#define GByte 1024 * MByte

namespace zinc {
namespace vm {
    class VirtualMachine {
    public:
        VirtualMachine();

        void initMemory(unsigned int size);
        void execute(std::list<Instruction> &instructions);

        // VM options
        static const unsigned int REG_COUNT = 16;
        static const unsigned int INIT_MEM_SIZE = 256 * KByte;

    private:
        CPU m_cpu;
        Memory m_mem;
        Register m_reg[REG_COUNT];
    };
}
}