#include <vm/VirtualMachine.hpp>

namespace zinc {
namespace vm {
    VirtualMachine::VirtualMachine() { }

    void VirtualMachine::execute(std::list<Instruction> &in)
    {
        m_instructions = in;
    }
}
}