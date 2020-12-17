#include <vm/Instruction.hpp>

namespace zinc {
namespace vm {
    Instruction::Instruction()
        : Instruction(0)
    {
    }

    Instruction::Instruction(uint64_t in) { m_instruction = in; }

}
}