#pragma once

#include "Instruction.h"
#include <list>

namespace zinc {
namespace vm {
    class VirtualMachine {
    public:
        VirtualMachine();
        int execute(std::list<Instruction> &instructions);

    private:
    };
}
}