#include "VirtualMachine.h"
#include "Instruction.h"
#include <iostream>

namespace zinc {
namespace vm {
    VirtualMachine::VirtualMachine() { }
    int VirtualMachine::execute(std::list<Instruction> &instructions)
    {
        for (auto &it : instructions) {
            std::cout << "Opcode: " << (int)it.getOpcode() << std::endl;
        }
        return 0;
    }
}
}