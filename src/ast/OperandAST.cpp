#include <ast/OperandAST.h>

namespace zinc {
namespace lang {
    OperandAST::OperandAST(Token &tok)
        : AST(tok, ASTType::Operand, 0)
    {
    }
}
}