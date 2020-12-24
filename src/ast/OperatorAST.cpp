#include <ast/AST.h>
#include <ast/OperatorAST.h>

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