#pragma once

// AST node class
#include <lang/Token.hpp>
#include <vector>
#include <memory>

namespace zinc {
namespace lang {
    // use for shorter names -> no need for the whole name every time
    class AST;
    using ASTPtr = std::unique_ptr<AST>;

    class AST {
    public:
        AST();
        AST(Token &tok, int nch);

        void setChild(int n, ASTPtr &node);
        void setNext(ASTPtr &node);

        ~AST();

    private:
        Token m_token;
        ASTPtr m_next;
        std::vector<ASTPtr> m_children;
    };
}
}