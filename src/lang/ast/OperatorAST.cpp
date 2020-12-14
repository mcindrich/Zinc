#include "lang/ast/AST.hpp"
#include <lang/ast/OperatorAST.hpp>

namespace zinc {
namespace lang {
    OperatorAST::OperatorAST(Token &tok, ASTPtr &left, ASTPtr &right)
        : AST(tok, ASTType::Operator, 2)
    {
        setChild(0, left);
        setChild(1, right);
    }
}
}