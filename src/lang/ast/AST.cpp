#include <lang/ast/AST.hpp>

namespace zinc {
namespace lang {
    AST::AST() { }
    AST::AST(Token &tok, int nch)
        : m_token(tok)
        , m_children(nch)
    {
    }
    void AST::setChild(int n, ASTPtr &node) { m_children[n] = std::move(node); }
    void AST::setNext(ASTPtr &node) { m_next = std::move(node); }

    AST::~AST() {}
}
}