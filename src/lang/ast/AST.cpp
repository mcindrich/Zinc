#include <lang/ast/AST.hpp>

namespace zinc {
namespace lang {
    AST::AST() { }
    AST::AST(Token &tok, ASTType type, int nch)
        : m_token(tok)
        , m_type(type)
    {
        if (nch > 0) {
            for (int i = 0; i < nch; i++) {
                m_children.push_back(ASTPtr(nullptr));
            }
        }
    }

    void AST::print(int ind)
    {
        for (int j = 0; j < ind; j++) {
            std::cout << "  ";
        }
        std::cout << "> [\"" << getToken().value << "\"]" << std::endl;
        for (int i = 0; i < getChildrenCount(); i++) {
            if (getChild(i)) {
                getChild(i)->print(ind + 1);
            }
        }
        if (getNext()) {
            getNext()->print(ind);
        }
    }

    void AST::setChild(int n, ASTPtr &node) { m_children[n] = std::move(node); }
    ASTPtr &AST::getChild(int n) { return m_children[n]; }

    void AST::setNext(ASTPtr &node) { m_next = std::move(node); }
    ASTPtr &AST::getNext() { return m_next; }

    Token &AST::getToken() { return m_token; }
    ASTType AST::getType() const { return m_type; }

    int AST::getChildrenCount() const { return m_children.size(); }

    AST::~AST() { }
}
}