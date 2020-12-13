#include <lang/ast/AST.hpp>

namespace zinc {
namespace lang {
    AST::AST() { }
    AST::AST(Token &tok, int nch)
        : m_token(tok)
    {
        if (nch > 0) {
            m_children.reserve(nch);
        }
    }

    void AST::setChild(int n, ASTPtr &node)
    {
        m_children.push_back(std::move(node));
        std::cout << m_children.size() << std::endl;
    }
    ASTPtr &AST::getChild(int n) { return m_children[n]; }

    void AST::setNext(ASTPtr &node) { m_next = std::move(node); }
    ASTPtr &AST::getNext() { return m_next; }

    Token &AST::getToken() { return m_token; }

    int AST::getChildrenCount() const { return m_children.size(); }

    AST::~AST() { }
}
}