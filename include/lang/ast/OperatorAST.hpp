#pragma once

// Operator AST node
#include <lang/ast/AST.hpp>
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