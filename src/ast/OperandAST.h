#pragma once

// Operator AST node
#include <ast/AST.h>
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