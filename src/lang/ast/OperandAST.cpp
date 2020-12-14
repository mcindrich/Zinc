#include <lang/ast/OperandAST.hpp>

namespace zinc {
namespace lang {
    OperandAST::OperandAST(Token &tok)
        : AST(tok, ASTType::Operand, 0)
    {
    }
}
}