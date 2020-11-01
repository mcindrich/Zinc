#pragma once

// AST node class
#include <lang/Token.hpp>
#include <vector>
#include <memory>

namespace zinc {
namespace lang {
    class AST {
    public:
        AST();
        AST(Token &tok, int nch);

        void setChild(int n, std::unique_ptr<AST> node);
        void setNext(std::unique_ptr<AST> node);

        virtual ~AST();

    private:
        Token m_token;
        std::unique_ptr<AST> m_next;
        std::vector<std::unique_ptr<AST>> m_children;
    };
}
}