#pragma once

// Operator AST node
#include <ast/AST.h>
#include <vector>
#include <memory>

namespace zinc {
namespace lang {
    class OperatorAST : public AST {
    public:
        OperatorAST(Token &tok, ASTPtr &left, ASTPtr &right);
    };
}
}