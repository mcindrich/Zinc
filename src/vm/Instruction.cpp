#include <vm/Instruction.hpp>

namespace zinc {
namespace vm {
    Instruction::Instruction()
        : m_instruction(0)
    {
    }

    void Instruction::setOpcode(Opcode val)
    {
        m_instruction |= uint32_t(val) << 26;
    }
    void Instruction::setR0(uint8_t val)
    {
        m_instruction |= uint32_t(val) << 20;
    }
    void Instruction::setR1(uint8_t val)
    {
        m_instruction |= uint32_t(val) << 16;
    }
    void Instruction::setR2(uint8_t val)
    {
        m_instruction |= uint32_t(val) << 12;
    }
    void Instruction::setExtraBits(uint8_t val)
    {
        m_instruction |= uint32_t(val) << 24;
    }
    void Instruction::set0RValue(uint32_t val)
    {
        m_instruction |= uint32_t(val) << 8;
    }
    void Instruction::set1RValue(uint32_t val)
    {
        m_instruction |= uint32_t(val) << 12;
    }
    void Instruction::set2RValue(uint32_t val)
    {
        m_instruction |= uint32_t(val) << 16;
    }

    Opcode Instruction::getOpcode() const
    {
        return Opcode((m_instruction >> 26) & 0b111111);
    }
    uint8_t Instruction::getR0() const
    {
        return (m_instruction >> 20) & 0b1111;
    }
    uint8_t Instruction::getR1() const
    {
        return (m_instruction >> 16) & 0b1111;
    }
    uint8_t Instruction::getR2() const
    {
        return (m_instruction >> 12) & 0b1111;
    }
    uint8_t Instruction::getExtraBits() const
    {
        return (m_instruction >> 24) & 0b11;
    }
    uint32_t Instruction::get0RValue() const
    {
        return (m_instruction << 8) >> 8;
    }
    uint32_t Instruction::get1RValue() const
    {
        return (m_instruction << 12) >> 12;
    }
    uint32_t Instruction::get2RValue() const
    {
        return (m_instruction << 16) >> 16;
    }

}
}