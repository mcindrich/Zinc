#pragma once

// Operator AST node
#include <lang/ast/AST.hpp>
#include <vector>
#include <memory>

namespace zinc {
namespace lang {
    class OperandAST : public AST {
    public:
        OperandAST(Token &tok);
    };
}
}