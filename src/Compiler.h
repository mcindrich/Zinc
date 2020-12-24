#pragma once

#include <Parser.h>
#include <list>

namespace zinc {
namespace lang {
    class Compiler {
    public:
        Compiler();

        void compile(std::string &prog_name);

    private:
        // compile using a parser and generate instructions from AST nodes
        Parser m_parser;
    };
}
}