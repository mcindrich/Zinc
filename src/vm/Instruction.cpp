#include <vm/Instruction.hpp>

namespace zinc {
namespace vm {
    Instruction::Instruction()
    {
        Instruction(0);
    }

    Instruction::Instruction(uint32_t in)
    {
        m_instruction = in;
    }

    Opcode Instruction::getOpcode() const
    {
        return (Opcode)(m_instruction & 0xff);
    }
}
}