#include <Compiler.h>

namespace zinc {
namespace lang {
    Compiler::Compiler() { }
    void Compiler::compile(std::string &prog_name)
    {
        m_parser.parseFile(prog_name);
    }

    std::list<vm::Instruction> &Compiler::getInstructions()
    {
        return m_instructions;
    }
}
}