#include <vm/VirtualMachine.hpp>

namespace zinc {
namespace vm {
    VirtualMachine::VirtualMachine() { }

    void VirtualMachine::execute(std::vector<Instruction> &in)
    {
        m_instructions = in;

        Instruction i1, i2, i3;

        // test for now => perform simple add operation
        i1.setOpcode(Opcode::Move);
        i1.setR0(0);
        i1.set1RValue(100);

        i2.setOpcode(Opcode::Move);
        i2.setR0(1);
        i2.set1RValue(100);

        i3.setOpcode(Opcode::Add);
        i3.setR0(0);
        i3.setR1(1);
        i3.setR2(2);

        m_instructions.push_back(i1);
        m_instructions.push_back(i2);
        m_instructions.push_back(i3);

        for (auto ip = m_instructions.begin(); ip != m_instructions.end();
             ip++) {
            switch (ip->getOpcode()) {
            case Opcode::Move:break;
            case Opcode::Add:
                break;
            default:
                break;
            }
        }
    }
}
}