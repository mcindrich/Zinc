#include <lang/ast/AST.hpp>

namespace zinc {
namespace lang {
    AST::AST() { }
    AST::AST(Token &tok, int nch)
        : m_token(tok)
        , m_children(nch)
    {
    }
    void AST::setChild(int n, std::unique_ptr<AST> node)
    {
        m_children[n] = std::move(node);
    }
    void AST::setNext(std::unique_ptr<AST> node) { m_next = std::move(node); }
}
}