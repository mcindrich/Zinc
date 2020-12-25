#include "Instruction.h"

namespace zinc {
namespace vm {
    Instruction::Instruction()
        : m_instruction(0)
    {
    }

    void Instruction::setOpcode(Opcode val)
    {
        m_instruction |= ((uint64_t)val) << (this->length - 6);
    }

    Opcode Instruction::getOpcode() const
    {
        return Opcode((m_instruction >> (this->length - 6)) & 0b111111);
    }
}
}