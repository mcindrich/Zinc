#pragma once

#include <lang/Parser.hpp>
#include <vm/Instruction.hpp>
#include <list>

namespace zinc {
namespace lang {
    class Compiler {
    public:
        Compiler();

        void compile(std::string &prog_name);

        std::list<vm::Instruction> &getInstructions();

    private:
        // compile using a parser and generate instructions from AST nodes
        Parser m_parser;
        // instructions to be generated
        std::vector<vm::Instruction> m_instructions;
    };
}
}