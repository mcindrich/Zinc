#include <lang/Compiler.hpp>

namespace zinc {
namespace lang {
    Compiler::Compiler() { }
    void Compiler::compile(std::string &prog_name)
    {
        m_parser.parseFile(prog_name);
    }
    std::vector<vm::Instruction> &Compiler::getInstructions()
    {
        return m_instructions;
    }
}
}