#pragma once

#include "Instruction.h"
#include <Parser.h>
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

        std::list<vm::Instruction> m_instructions;
    };
}
}